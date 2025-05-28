#include <WiFi.h>
#include <WebServer.h>
#include <driver/i2s.h>

const char* ssid = "TWOJA_SIEC_WIFI";
const char* password = "TWOJE_HASLO_WIFI";

WebServer server(80);

#define I2S_WS 25
#define I2S_SD 33
#define I2S_SCK 26
#define BUFFER_SIZE 1024

void setupI2S() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 4,
    .dma_buf_len = BUFFER_SIZE,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_SD
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
}

float readRMS() {
  int16_t buffer[BUFFER_SIZE];
  size_t bytes_read;
  i2s_read(I2S_NUM_0, &buffer, sizeof(buffer), &bytes_read, portMAX_DELAY);

  int samples = bytes_read / sizeof(int16_t);
  float sum = 0;

  for (int i = 0; i < samples; i++) {
    sum += buffer[i] * buffer[i];
  }

  return sqrt(sum / samples);
}

const char html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head><meta charset="utf-8" /><title>IRIA - Mikrofon RMS</title></head>
<body><h2>Aktualny RMS</h2>
<canvas id="chart" width="600" height="300" style="border:1px solid black;"></canvas>
<script>
const canvas = document.getElementById("chart");
const ctx = canvas.getContext("2d");
const width = canvas.width;
const height = canvas.height;
const data = [];
function draw() {
  ctx.clearRect(0, 0, width, height);
  ctx.beginPath();
  ctx.moveTo(0, height - data[0]);
  for (let i = 1; i < data.length; i++) {
    ctx.lineTo(i * (width / data.length), height - data[i]);
  }
  ctx.stroke();
}
async function fetchRMS() {
  const res = await fetch("/rms");
  const val = parseFloat(await res.text());
  data.push(val * 3);
  if (data.length > 100) data.shift();
  draw();
}
setInterval(fetchRMS, 300);
</script></body></html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  setupI2S();
  server.on("/", []() { server.send_P(200, "text/html", html); });
  server.on("/rms", []() {
    float rms = readRMS();
    server.send(200, "text/plain", String(rms));
  });
  server.begin();
}

void loop() {
  server.handleClient();
}

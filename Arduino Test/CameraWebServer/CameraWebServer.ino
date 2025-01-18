/*----------수정 금지----------*/
#include "esp_camera.h"
#include <WiFi.h>

// 경고: UXGA 해상도와 고품질 JPEG를 위해 PSRAM IC가 필요합니다
// ESP32 Wrover 모듈 또는 PSRAM이 있는 다른 보드를 선택해야 합니다
// 이미지가 버퍼 크기를 초과하면 부분 이미지가 전송됩니다

// 카메라 모델 선택
//#define CAMERA_MODEL_WROVER_KIT // PSRAM이 있는 모델
//#define CAMERA_MODEL_ESP_EYE // PSRAM이 있는 모델
//#define CAMERA_MODEL_M5STACK_PSRAM // PSRAM이 있는 모델
//#define CAMERA_MODEL_M5STACK_V2_PSRAM // M5Camera 버전 B, PSRAM이 있음
//#define CAMERA_MODEL_M5STACK_WIDE // PSRAM이 있는 모델
//#define CAMERA_MODEL_M5STACK_ESP32CAM // PSRAM이 없는 모델
#define CAMERA_MODEL_AI_THINKER // PSRAM이 있는 모델
//#define CAMERA_MODEL_TTGO_T_JOURNAL // PSRAM이 없는 모델

#include "camera_pins.h" // 카메라 핀 정의 포함

// const char* ssid = "oldcast1e"; // WiFi SSID 설정
// const char* password = "dlgjstjd"; // WiFi 비밀번호 설정

const char* ssid = "sejong-guest"; // WiFi SSID 설정
const char* password = "0234083114"; // WiFi 비밀번호 설정

void startCameraServer(); // 카메라 서버 시작 함수 선언

void setup() {
  Serial.begin(115200); // 시리얼 통신 시작 및 속도 설정
  Serial.setDebugOutput(true); // 디버그 출력 설정
  Serial.println(); // 빈 줄 출력

  camera_config_t config; // 카메라 설정 구조체 선언
  config.ledc_channel = LEDC_CHANNEL_0; // LED 컨트롤 채널 설정
  config.ledc_timer = LEDC_TIMER_0; // LED 타이머 설정
  config.pin_d0 = Y2_GPIO_NUM; // 데이터 핀 설정
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM; // XCLK 핀 설정
  config.pin_pclk = PCLK_GPIO_NUM; // PCLK 핀 설정
  config.pin_vsync = VSYNC_GPIO_NUM; // VSYNC 핀 설정
  config.pin_href = HREF_GPIO_NUM; // HREF 핀 설정
  config.pin_sscb_sda = SIOD_GPIO_NUM; // SSCB SDA 핀 설정
  config.pin_sscb_scl = SIOC_GPIO_NUM; // SSCB SCL 핀 설정
  config.pin_pwdn = PWDN_GPIO_NUM; // PWDN 핀 설정
  config.pin_reset = RESET_GPIO_NUM; // 리셋 핀 설정
  config.xclk_freq_hz = 20000000; // XCLK 주파수 설정
  config.pixel_format = PIXFORMAT_JPEG; // 픽셀 형식 설정 (JPEG)
  
  // PSRAM이 있으면 UXGA 해상도와 높은 JPEG 품질로 초기화
  // 더 큰 프레임 버퍼를 미리 할당
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA; // 해상도 설정
    config.jpeg_quality = 10; // JPEG 품질 설정 (낮을수록 품질 좋음)
    config.fb_count = 2; // 프레임 버퍼 수 설정
  } else {
    config.frame_size = FRAMESIZE_SVGA; // PSRAM이 없으면 해상도 낮춤
    config.jpeg_quality = 12; // JPEG 품질 설정 (낮을수록 품질 좋음)
    config.fb_count = 1; // 프레임 버퍼 수 설정
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP); // 특정 카메라 모델의 핀 설정
  pinMode(14, INPUT_PULLUP);
#endif

  // 카메라 초기화
  esp_err_t err = esp_camera_init(&config); // 카메라 초기화 함수 호출
  if (err != ESP_OK) { // 초기화 실패 시
    Serial.printf("Camera init failed with error 0x%x", err); // 오류 메시지 출력
    return; // 함수 종료
  }

  sensor_t * s = esp_camera_sensor_get(); // 카메라 센서 정보 가져오기
  // 초기 센서는 수직으로 뒤집혀 있고 색상이 약간 과포화됨
  if (s->id.PID == OV3660_PID) { // 특정 센서 ID 확인
    s->set_vflip(s, 1); // 수직으로 뒤집기 설정
    s->set_brightness(s, 1); // 밝기 약간 올리기
    s->set_saturation(s, -2); // 채도 낮추기
  }
  // 이미지 180도 회전 설정
  s->set_vflip(s, 1); // 수직 플립 설정
  s->set_hmirror(s, 1); // 수평 미러링 설정

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1); // 특정 카메라 모델의 수직 플립 설정
  s->set_hmirror(s, 1); // 수평 미러링 설정
#endif

  WiFi.begin(ssid, password); // WiFi 연결 시작

  while (WiFi.status() != WL_CONNECTED) { // WiFi 연결 대기
    delay(500); // 500ms 대기
    Serial.print("."); // 진행 표시 출력
  }
  Serial.println("");
  Serial.println("WiFi connected"); // WiFi 연결 완료 메시지 출력

  startCameraServer(); // 카메라 서버 시작

  Serial.print("Camera Ready! Use 'http://"); 
  Serial.print(WiFi.localIP()); // 로컬 IP 주소 출력
  Serial.println("' to connect"); // 연결 주소 출력
}

void loop() {
  // 메인 코드 반복 실행
  delay(10000); // 10초 대기
}

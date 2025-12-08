
#define L_TRIG D3
#define L_ECHO D2
#define R_TRIG D5
#define R_ECHO D1

// --- VOLUME CONTROL CONSTANTS ---
const int DETECT_MIN = 4;
const int DETECT_MAX = 40;
const int MOVE_THRESHOLD = 8;        // change needed for inc/dec
const int VOL_REPEAT_TIME = 150;     // repeat rate
const int HAND_LOST_TIME = 2000;     // 2 sec no-hand → reset base

// volume control state
long baseDist = -1;
bool handActive = false;
unsigned long lastSeen = 0;
unsigned long lastStep = 0;

// === DISTANCE & TIMING ===
unsigned long now;
const int DETECT_DIST = 35;
const int HOLD_TOL = 4;
const int SWIPE_TIMEOUT = 450;

const int PLAY_PAUSE_TIME = 800;
const int MODE_HOLD = 1000;

int mode = 0;  // 0 = MEDIA, 1 = VOLUME

bool lActive = false, rActive = false;
unsigned long lStart = 0, rStart = 0;
long lRef = 999, rRef = 999;

bool swipeActive = false;
bool swipeLeftToRight = false;
unsigned long swipeStart = 0;


long getDist(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 25000);
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}

bool steady(long dist, long ref){
  return abs(dist - ref) <= HOLD_TOL;
}


void setup(){
  Serial.begin(115200);

  pinMode(L_TRIG, OUTPUT);
  pinMode(R_TRIG, OUTPUT);
  pinMode(L_ECHO, INPUT);
  pinMode(R_ECHO, INPUT);

  Serial.println("System Ready");
}


void loop(){
  now = millis();
  long dL = getDist(L_TRIG, L_ECHO);
  long dR = getDist(R_TRIG, R_ECHO);

  bool lDetected = (dL < DETECT_DIST);
  bool rDetected = (dR < DETECT_DIST);

 
  // LEFT sensor initial detection

  if (lDetected && !lActive){
    lActive = true; lStart = now; lRef = dL;
  }
  if (!lDetected) lActive = false;

  // RIGHT sensor initial detection
  
  if (rDetected && !rActive){
    rActive = true; rStart = now; rRef = dR;
  }
  if (!rDetected) rActive = false;


  // MODE SWITCH (LEFT SENSOR HOLD)

  if (lActive && steady(dL, lRef) && now - lStart >= MODE_HOLD){
      mode = !mode;
      Serial.println(mode == 0 ? "MODE: MEDIA" : "MODE: VOLUME");

      // reset volume base when switching mode
      baseDist = -1;
      handActive = false;

      delay(1000);
      return;
  }

 
  // PLAY/PAUSE (RIGHT SENSOR HOLD)
  
  if (mode == 0){
    if (rActive && steady(dR, rRef)){
      if (now - rStart >= PLAY_PAUSE_TIME){
          Serial.println("PLAY_PAUSE");
          delay(1000);
          return;
        }
      }
    }

  
  // MEDIA MODE SWIPES
  
  if (mode == 0){

    if (!swipeActive){
      if (lDetected){
        swipeActive = true; swipeLeftToRight = true; swipeStart = now;
      } else if (rDetected){
        swipeActive = true; swipeLeftToRight = false; swipeStart = now;
      }
    }

    if (swipeActive){
      if (swipeLeftToRight && rDetected && (now - swipeStart < SWIPE_TIMEOUT)){
        Serial.println("NEXT_TRACK");
        swipeActive = false;
        return;
      }
      if (!swipeLeftToRight && lDetected && (now - swipeStart < SWIPE_TIMEOUT)){
        Serial.println("PREV_TRACK");
        swipeActive = false;
        return;
      }
      if (now - swipeStart > SWIPE_TIMEOUT){
        swipeActive = false;
      }
    }
  }

  
  //           VOLUME MODE (NEW CLEAN LOGIC)
  
  if (mode == 1){

    // use RIGHT sensor only for volume control
    long d = dR;
    bool detected = (d >= DETECT_MIN && d <= DETECT_MAX);

    // hand not detected
    if (!detected){
      if (handActive && (now - lastSeen > HAND_LOST_TIME)){
        handActive = false;
        baseDist = -1;
        Serial.println("HAND LOST → RESET BASE");
      }
      return;
    }

    lastSeen = now;

    // set baseline once
    if (!handActive){
      handActive = true;
      baseDist = d;
      lastStep = now;

      Serial.print("BASE SET: ");
      Serial.println(baseDist);
      return;
    }

    // continuous control
    long diff = d - baseDist;

    if (diff >= MOVE_THRESHOLD-2){
      if (now - lastStep >= VOL_REPEAT_TIME){
        lastStep = now;
        Serial.println("VOLUME_DOWN");
      }
    }
    else if (diff <= -MOVE_THRESHOLD){
      if (now - lastStep >= VOL_REPEAT_TIME){
        lastStep = now;
        Serial.println("VOLUME_UP");
      }
    }
  }
}

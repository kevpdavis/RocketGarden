

enum STATE {INITIALIZATION, PRELAUNCH, THRUST, ASCENTCOAST, DESCENTDROGUE, DESCENTMAIN};

enum STATE state;

float deltaAlt;

float startAltitude;
float lastAltitude;
float currentAltitude;
float mainsAltitude;

int ledStatusPin = 13;

void doInit()
{
  startAltitude = 57.0;
  currentAltitude = 57.0;
  lastAltitude = 57.0;
  mainsAltitude = 200.0;
  //get startAltitude 
}

void sendTelemetry()
{
  Serial.print("Altitude: ");
  Serial.print(currentAltitude);
  Serial.print("\tdeltaAlt: ");
  Serial.print(deltaAlt);
  Serial.print("\tState: ");
  Serial.println(state);
}

void readAltitude()
{
  lastAltitude = currentAltitude;
  currentAltitude = currentAltitude + deltaAlt;
}

void readBMP180()
{
  
}

bool launchDetect()
{
  return ((currentAltitude - startAltitude) > 100.0);
}

bool checkApogee()
{
  return (currentAltitude < lastAltitude);  //we're going down, now! NOTE: This will fail if going supersonic, need to inhibit for a time
}


bool checkSecondary()
{
  return (currentAltitude <= mainsAltitude);
}
  


void setup()
{
  state = INITIALIZATION;
  Serial.begin(9600);
  while(!Serial) {
    ; // wait for serial to connect, some Leonardo thing? shouldn't hurt to include
  }
  pinMode(ledStatusPin, OUTPUT);
  digitalWrite(ledStatusPin, LOW);
  deltaAlt = 5.0;
}


void loop()
{
  // INITIALIZATION, PRELAUNCH, THRUST, ASCENTCOAST, DESCENTDROGUE, DESCENTMAIN
  switch(state)
  {
    case INITIALIZATION:
      doInit();
      state = PRELAUNCH;
      break;
    
    case PRELAUNCH:
      if (launchDetect()) {
        state = THRUST;
      }
      break;
    
    case THRUST:      
      state = ASCENTCOAST; // don't use for now, preferable use accel to determine
      break;
    
    case ASCENTCOAST:
        deltaAlt = deltaAlt - 0.1;
        if(checkApogee())  {
          deltaAlt = -0.4;
          state = DESCENTDROGUE;
        }
      break;
    
    case DESCENTDROGUE:
        if(checkSecondary())  {
          state = DESCENTMAIN;
          deltaAlt = -0.1;
        }
        digitalWrite(ledStatusPin, HIGH);
        break;
    
    case DESCENTMAIN:
      ;
      break;
    
    default:
      Serial.println("ERROR: Undefined State"); 
  }
  
  readAltitude();
  sendTelemetry();
}

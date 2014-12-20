
enum STATE {INITIALIZATION, PRELAUNCH, THRUST, ASCENTCOAST, DESCENTDROGUE, DESCENTMAIN};

enum STATE state;
float startAltitude;
float currentAltitude;
float mainsAltitude;

void doInit()
{
  //get startAltitude 
}

void sendTelemetry()
{
  
}

void readAltitude()
{
  
}

void readBMP180()
{
  
}

bool launchDetect()
{
  return ((currentAltitude - startAltitude) > 100.0);
}


void setup()
{
  state = INITIALIZATION;
  Serial.begin(9600);
  while(!Serial) {
    ; // wait for serial to connect, some Leonardo thing? shouldn't hurt to include
  }
}


void loop()
{
  // INITIALIZATION, PRELAUNCH, THRUST, ASCENTCOAST, DESCENTDROGUE, DESCENTMAIN
  switch(state)
  {
    case INITIALIZATION:
      doInit();
      break;
    
    case PRELAUNCH:
      if (launchDetect()) {
        state = PRELAUNCH;
      }
      break;
    
    case THRUST:
      state = ASCENTCOAST; // don't use for now, preferable use accel to determine
      break;
    
    case ASCENTCOAST:
        //check for apogee
      break;
    
    case DESCENTDROGUE:
        //check for mains altitude
      break;
    
    case DESCENTMAIN:
      
      break;
    
}

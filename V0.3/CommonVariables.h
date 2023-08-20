#include <Arduino.h>


//Developer Logic
extern bool DeveloperMode;
static const int WipersPin = 14 ;
static const int FullSwipeButton = 15 ;
static const int ConstantSwippingButton = 12 ;
static const int WipeWhileHoldedButton = 13 ;

//Wiping Variables
extern bool ConstantLoopWiping;

extern bool WipesAreSuppostToMove;

extern int WipesToDo;
extern int WaitMilliSeconds;

static const int MaxWipes = 5;





//networking
static const char *ssid = "ChillNetwork";
static const char *password = "Ch1llBr0!";
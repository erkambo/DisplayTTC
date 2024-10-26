#include <Arduino.h>
#include <vector>
#include <WifiClientSecure.h>



// put declatations here


//struct for stops
struct stopLocationStruct
{
int stopid;
String Name;
int LEDindex; //leds corresponding to stops
};

//Bindings for yellow
std::vector<stopLocationStruct> yellowLineStopInstructions= {
  {14111,"Finch Station - Southbound Platform",1},
  {13789,"North York Centre Station - Southbound Platform",2},
  {13860,"Sheppard-Yonge Station - Southbound Platform",3},
  {13792,"York Mills Station - Southbound Platform",4},
  {13792,"York Mills Station - Southbound Platform",5},
  {13793,"Lawrence Station - Southbound Platform",6},
  {13795,"Eglinton Station - Southbound Platform",7},
  {13798,"Davisville Station - Southbound Platform",8},
  {13799,"St Clair Station - Southbound Platform",9},
  {13802,"Summerhill Station - Southbound Platform",10},
  {13803,"Rosedale Station - Southbound Platform",11},
  {13864,"Bloor Station - Southbound Platform",12},
  {13806,"Wellesley Station - Southbound Platform",13},
  {13807,"College Station - Southbound Platform",14},
  {13810,"Dundas Station - Southbound Platform",15},
  {13811,"Queen Station - Southbound Platform",16},
  {13814,"King Station - Southbound Platform",17},
  {13817,"St Andrew Station - Northbound Platform",18},
  {13820,"Osgoode Station - Northbound Platform",19},
  {13821,"St Patrick Station - Northbound Platform",20},
  {13824,"Queen's Park Station - Northbound Platform",21},
  {13825,"Museum Station - Northbound Platform",22},
  {13858,"St George Station - Northbound Platform",23},
  {13853,"Spadina Station - Northbound Platform",24},
  {13828,"Dupont Station - Northbound Platform",25},
  {13829,"St Clair West Station - Northbound Platform",26},
  {13832,"Eglinton West Station - Northbound Platform",27},
  {13833,"Glencairn Station - Northbound Platform",28},
  {13836,"Lawrence West Station - Northbound Platform",29},
  {13837,"Yorkdale Station - Northbound Platform",30},
  {13840,"Wilson Station - Northbound Platform",31},
  {14945,"Sheppard West Station - Subway Platform",32},
  {15664,"Downsview Park Station - Northbound Platform",33},
  {15659,"Finch West Station - Northbound Platform",34},
  {15666,"York University - Northbound Platform",35},
  {15656,"Pioneer Village Station - Northbound Platform",36},
  {15661,"Highway 407 Station - Northbound Platform",37},
  {15662,"Vaughan Metropolitan Centre Station - Northbound Platform",38},
};

//Bindings for green
std::vector<stopLocationStruct> greenLineStopInstructions= {
  {13785,"Kipling Station - Eastbound Platform",39},
  {13784,"Islington Station - Eastbound Platform",40},
  {13784,"Islington Station - Eastbound Platform",41},
  {13781,"Royal York Station - Eastbound Platform",42},
  {13780,"Old Mill Station - Eastbound Platform",43},
  {13777,"Jane Station - Eastbound Platform",44},
  {13776,"Runnymede Station - Eastbound Platform",45},
  {13773,"High Park Station - Eastbound Platform",46},
  {13772,"Keele Station - Eastbound Platform",47},
  {13769,"Dundas West Station - Eastbound Platform",48},
  {13768,"Lansdowne Station - Eastbound Platform",49},
  {13765,"Dufferin Station - Eastbound Platform",50},
  {13764,"Ossington Station - Eastbound Platform",51},
  {13761,"Christie Station - Eastbound Platform",52},
  {13760,"Bathurst Station - Eastbound Platform",53},
  {13852,"Spadina Station - Eastbound Platform",54},
  {13856,"St George Station - Eastbound Platform",55},
  {13856,"St George Station - Eastbound Platform",56},
  {13757,"Bay Station - Eastbound Platform",57},
  {13756,"Yonge Station - Eastbound Platform",58},
  {13753,"Sherbourne Station - Eastbound Platform",59},
  {13752,"Castle Frank Station - Eastbound Platform",60},
  {13749,"Broadview Station - Eastbound Platform",61},
  {13748,"Chester Station - Eastbound Platform",62},
  {13746,"Pape Station - Eastbound Platform",63},
  {13743,"Donlands Station - Eastbound Platform",64},
  {13742,"Greenwood Station - Eastbound Platform",65},
  {13739,"Coxwell Station - Eastbound Platform",66},
  {13738,"Woodbine Station - Eastbound Platform",67},
  {13735,"Main Street Station - Eastbound Platform",68},
  {13734,"Victoria Park Station - Eastbound Platform",69},
  {13732,"Warden Station - Eastbound Platform",70},
  {14947,"Kennedy Station - Subway Platform",71},
};

//Bindings for Purple
std::vector<stopLocationStruct> purpleStopLocations
{
  {13862,"Sheppard-Yonge Station - Eastbound Platform",72},
  {13844,"Bayview Station - Eastbound Platform",73},
  {13845,"Bessarion Station - Eastbound Platform",74},
  {13848,"Leslie Station - Eastbound Platform",75},
  {14949,"Don Mills Station - Subway Platform",76},
};



void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:

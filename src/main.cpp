#include <Arduino.h>
#include <vector>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

// WiFi Settings
const char* ssid = "Banana Guest";
const char* password = "Banana1245";

// Server connection
const char* server = "ntas.ttc.ca";
WiFiClientSecure client;

// HTTPS Certificate for connection
const char *certificate = "-----BEGIN CERTIFICATE-----\n"
                           "MIIDXzCCAkegAwIBAgILBAAAAAABIVhTCKIwDQYJKoZIhvcNAQELBQAwTDEgMB4G\n" 
                           "A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjMxEzARBgNVBAoTCkdsb2JhbFNp\n" 
                           "Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDkwMzE4MTAwMDAwWhcNMjkwMzE4\n" 
                           "MTAwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMzETMBEG\n" 
                           "A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI\n" 
                           "hvcNAQEBBQADggEPADCCAQoCggEBAMwldpB5BngiFvXAg7aEyiie/QV2EcWtiHL8\n" 
                           "RgJDx7KKnQRfJMsuS+FggkbhUqsMgUdwbN1k0ev1LKMPgj0MK66X17YUhhB5uzsT\n"
                           "gHeMCOFJ0mpiLx9e+pZo34knlTifBtc+ycsmWQ1z3rDI6SYOgxXG71uL0gRgykmm\n"
                           "KPZpO/bLyCiR5Z2KYVc3rHQU3HTgOu5yLy6c+9C7v/U9AOEGM+iCK65TpjoWc4zd\n"
                           "QQ4gOsC0p6Hpsk+QLjJg6VfLuQSSaGjlOCZgdbKfd/+RFO+uIEn8rUAVSNECMWEZ\n"
                           "XriX7613t2Saer9fwRPvm2L7DWzgVGkWqQPabumDk3F2xmmFghcCAwEAAaNCMEAw\n"
                           "DgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wHQYDVR0OBBYEFI/wS3+o\n"
                           "LkUkrk1Q+mOai97i3Ru8MA0GCSqGSIb3DQEBCwUAA4IBAQBLQNvAUKr+yAzv95ZU\n"
                           "RUm7lgAJQayzE4aGKAczymvmdLm6AC2upArT9fHxD4q/c2dKg8dEe3jgr25sbwMp\n"
                           "jjM5RcOO5LlXbKr8EpbsU8Yt5CRsuZRj+9xTaGdWPoO4zzUhw8lo/s7awlOqzJCK\n"
                           "6fBdRoyV3XpYKBovHd7NADdBj+1EbddTKJd+82cEHhXXipa0095MJ6RMG3NzdvQX\n"
                           "mcIfeg7jLQitChws/zyrVQ4PkX4268NXSb7hLi18YIvDQVETI53O9zJrlAGomecs\n"
                           "Mx86OyXShkDOOyyGeMlhLxS67ttVb9+E7gUJTb0o2HLO02JQZR7rkpeDMdmztcpH\n"
                           "WD9f\n"
                           "-----END CERTIFICATE-----\n";

// Struct for stops
struct stopLocationStruct {
    int stopid;
    String Name;
    int LEDindex; // LEDs corresponding to stops
};

// Bindings for Yellow Line
std::vector<stopLocationStruct> yellowLineStopInstructions = {
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

// Bindings for Green Line
std::vector<stopLocationStruct> greenLineStopInstructions = {
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

// Bindings for Purple Line
std::vector<stopLocationStruct> purpleStopLocations = {
    {13862,"Sheppard-Yonge Station - Eastbound Platform",72},
    {13844,"Bayview Station - Eastbound Platform",73},
    {13845,"Bessarion Station - Eastbound Platform",74},
    {13848,"Leslie Station - Eastbound Platform",75},
    {14949,"Don Mills Station - Subway Platform",76},
};

// A vector of vectors containing all stop locations
std::vector<std::vector<stopLocationStruct>> allThreeStopLocs = {yellowLineStopInstructions, greenLineStopInstructions, purpleStopLocations};

// JSON Text Storage
String jsonText;

// Sample Stops (for debug purposes)
//int samplestops[3] = {13757,13742,14947};

// JSON Document Size
const size_t JSON_DOC_SIZE = 1024; //consistently less than 1024

void setup() {
    // Initialize Serial and wait for port to open
    Serial.begin(115200);
    delay(1000);
    Serial.print(".");

    // Initialize WiFi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Attempting Connection to Wifi network ..");

    // Attempt to connect to WiFi network
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000); // Wait 1 second before retrying
    }

    Serial.println("\nConnected to WiFi!");
    Serial.println(WiFi.localIP());
}

//function to connect to server for individual stops
String apiconnection(const char* servername, int stopID) { 
    HTTPClient http;
    String serverLink = String("https://") + servername + "/api/ntas/get-next-train-time/" + String(stopID);
    http.begin(serverLink, certificate); // Begin connection with certificate for HTTPS

    int httpResponseCode = http.GET();
    String response = "";

    if (httpResponseCode > 0) {
        response = http.getString(); // Get the response payload
        Serial.printf("Response code for Stop ID %d: %d\n", stopID, httpResponseCode);

    } else {
        Serial.printf("Error code for Stop ID %d: %d\n", stopID, httpResponseCode);
    }

    http.end(); // End HTTP connection
    return response;
}

void loop() {
    // Start GET request
    Serial.println("\n--- Starting GET Requests ---");

    // go through each line (Yellow, Green, Purple)
    for(int k = 0; k < allThreeStopLocs.size(); k++ ){
        std::vector<stopLocationStruct> stopLocations = allThreeStopLocs.at(k); // Get the current line's stops

        // Iterate through each stop in the current line (Yellow -> Green -> Purple)
        for(int i = 0; i < stopLocations.size(); i++){
            int currentStopID = stopLocations.at(i).stopid;
            String stopName = stopLocations.at(i).Name;
            int ledIndex = stopLocations.at(i).LEDindex;

            Serial.printf("\nFetching data for Stop ID: %d (%s)\n", currentStopID, stopName.c_str());

            // Call API for the current stop
            jsonText = apiconnection(server, currentStopID);

            // Check if response is not empty (never happens unless they changed stop code)
            if (jsonText.length() == 0) {
                Serial.println("No response received.");
                continue; // Skip to the next stop if there's no response
            }

            // Create a JSON document
            DynamicJsonDocument doc(JSON_DOC_SIZE);

            // Deserialize the JSON (split it aparty)
            DeserializationError error = deserializeJson(doc, jsonText);

            // Check for deserialization errors
            if (error) {
                Serial.print("deserializeJson() failed: ");
                Serial.println(error.c_str());
                continue; // Skip to next stop if there's an error
            }

            // Check if the JSON is an array and has at least one element
            if (!doc.is<JsonArray>() || doc.size() == 0) {
                Serial.println("Unexpected JSON format");
                continue;
            }
                        Serial.println("HERE"); //debug purposes

            // Access the first object in the array
            JsonObject firstTrainInfo = doc[0].as<JsonObject>();

            // Extract the 'nextTrains' field
            const char* nextTrains = firstTrainInfo["nextTrains"];

            // Check if 'nextTrains' exists
            if (nextTrains) {
                Serial.printf("Next Trains for Stop %d (%s): %s\n", 
                              currentStopID, 
                              stopName.c_str(), 
                              nextTrains);
                if(nextTrains[0] == '0' ){
                    Serial.println("LED ON");
                }
            } else {
                Serial.println("'nextTrains' field not found.");
            }
            // Add a short delay to avoid overwhelming the server
            delay(100);
        }
    }

    Serial.println("\n--- Cycle Completed ---");

    delay(10000); // Wait for 10 seconds
}

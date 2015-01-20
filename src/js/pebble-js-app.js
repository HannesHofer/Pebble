/* get GPS coordinates from Phone */

var locationOptions = {
  enableHighAccuracy: false, 
  maximumAge: 600000, 
  timeout: 60000
};

var savedOptions = {
  'language': 2,
  'dateformat': 1,
  'showseconds': 1,
  'nomovement': 300,
  'sunrise': 1,
  'bluetooth': 1,
  'bat': 1 };

function locationSuccess(pos) {
  // sendAppMessage converts values to uin32_t therefore convert to int
  var coordinates = pos.coords;
  var utcOffset = new Date().getTimezoneOffset();
  // ATTENTION: it seems that pebble reports inverted getTimezoneOffset
  // this is fixed here for now but need further checking when app is updated
  utcOffset *= -1;
  Pebble.sendAppMessage({"longitude": Math.round(coordinates.longitude * 1000000),
                         "latitude":  Math.round(coordinates.latitude * 1000000),
                         "utcoffset":  utcOffset});

}

function locationError(err) {
  // GPS_INVALID = 99999
  Pebble.sendAppMessage({"longitude": 99999,
                         "latitude":  99999,
                         "utcoffset": 99999});
}

Pebble.addEventListener('appmessage',
  function(e) {
    navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
  }
);

Pebble.addEventListener('ready', 
  function(e) {
    navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
  }
);


///////////////// configuration ///////////////
Pebble.addEventListener("showConfiguration", function() {
 // var val = window.localStorage.getItem("gibsnit");
  Pebble.openURL('http://hanneshofer.github.io/Pebble/?'+encodeURIComponent(JSON.stringify(savedOptions)));

  
});

Pebble.addEventListener("webviewclosed", function(e) {
  console.log("configuration closed");
  // webview closed
  //Using primitive JSON validity and non-empty check
  if (e.response.charAt(0) == "{" && e.response.slice(-1) == "}" && e.response.length > 5) {
  options = JSON.parse(decodeURIComponent(e.response));
  console.log("Options = " + JSON.stringify(options));
  } else {
  console.log("Cancelled");
  }
});
/* get GPS coordinates from Phone */

var locationOptions = {
  enableHighAccuracy: false, 
  maximumAge: 600000, 
  timeout: 60000
};

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
  var settings = window.localStorage.getItem("settings");
  if (settings == null) {
    settings = {
      'showseconds': 1,
      'sunrise': 1,
      'nomovement': 300,
      'language': 2,
      'dateformat': 1,
      'bat': 1, 
      'bluetooth': 1};
    settings = JSON.stringify(settings);
  }
  console.log("settings:" + settings);
  Pebble.openURL('http://hanneshofer.github.io/Pebble/?'+encodeURIComponent(settings));
});

Pebble.addEventListener("webviewclosed", function(e) {
  console.log("configuration closed");
  // webview closed
  //Using primitive JSON validity and non-empty check
  if (e.response.charAt(0) == "{" && e.response.slice(-1) == "}" && e.response.length > 5) {
  var settings = JSON.parse(decodeURIComponent(e.response));
  window.localStorage.setItem("settings", JSON.stringify(settings));
  Pebble.sendAppMessage(settings);
  console.log("Options = " + JSON.stringify(settings));
  } else {
  console.log("Cancelled");
  }
});
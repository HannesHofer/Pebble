/* get GPS coordinates from Phone */

var locationOptions = {
  enableHighAccuracy: false, 
  maximumAge: 10000, 
  timeout: 60000
};


function locationSuccess(pos) {
  // sendAppMessage converts values to uin32_t therefore convert to int
  var coordinates = pos.coords;
  Pebble.sendAppMessage({"longitude": Math.round(coordinates.longitude * 1000000),
                         "latitude":  Math.round(coordinates.latitude * 1000000)});

}

function locationError(err) {
  // GPS_INVALID = 99999
  Pebble.sendAppMessage({"longitude": 99999,
                         "latitude":  99999});
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

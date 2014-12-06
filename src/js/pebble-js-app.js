/* get GPS coordinates from Phone */

var locationOptions = {
  enableHighAccuracy: false, 
  maximumAge: 10000, 
  timeout: 10000
};


function locationSuccess(pos) {
  // sendAppMessage converts values to uin32_t therefore convert to int
  Pebble.sendAppMessage({"longitude": Math.round(coordinates.longitude * 1000000),
                         "latitude":  Math.round(coordinates.latitude * 1000000)});

}

function locationError(err) {
  // nothing to do on error
}

Pebble.addEventListener('appmessage',
  function(e) {
    navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
  }
);



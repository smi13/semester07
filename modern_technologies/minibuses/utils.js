Utils = function () {
}

Utils.initialize = function () {
    google.maps.MVCArray.prototype.clear = function (){
        for (var i = this.getLength(); i > 0; this.removeAt(--i));
    }
}

Utils.clearMarkers = function () {
    if (markers) {
       for (i in markers) {
           markers[i].setMap(null);
        }
        markers = [];
    }
}

Utils.deg2rad = function (x) {
    return x * Math.PI / 180;
}

Utils.distHaversine = function (p1, p2) {
  var R = 6371; // earth's mean radius in km
  var dLat  = Utils.deg2rad(p2.lat() - p1.lat());
  var dLong = Utils.deg2rad(p2.lng() - p1.lng());

  var a = Math.sin(dLat/2) * Math.sin(dLat/2) +
          Math.cos(Utils.deg2rad(p1.lat())) * Math.cos(Utils.deg2rad(p2.lat())) *
          Math.sin(dLong/2) * Math.sin(dLong/2);
  var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
  var d = R * c;

  return d.toFixed(3);
}
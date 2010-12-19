var polytech = new google.maps.LatLng(60.00879915725471, 30.369670088291166);
var map;

minibuses = function () {
}

minibuses.initialize = function () {
    var map_options = {
        zoom: 16,
        scrollwheel: true,
        center: polytech,
        navigationControl: false,
        streetViewControl: false,
        mapTypeControl: false,
        scaleControl: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP
    };

    map = new google.maps.Map(document.getElementById("map_canvas"),
        map_options);
        
    UIElements.initialize();
    ControlHandlers.initialize();
}
var button_finish_name = "Finish route";
var add_event_handle;
var poly, markers = [];

ControlHandlers = function () {
}

ControlHandlers.goHome = function () {
    map.setCenter(polytech);
}

ControlHandlers.initialize = function () {
    var polyOptions = {
      strokeColor: '#000000',
      strokeOpacity: 1.0,
      strokeWeight: 3
    }

    poly = new google.maps.Polyline(polyOptions);
    poly.setMap(map);
}

showRoute_ = function () {
}

ControlHandlers.showRoute = function () {
    $.getJSON("get_route.php", {name: this.title},
        function (event) {
            var route = event.result.split(",");

            poly.getPath().clear();
            Utils.clearMarkers();

            for (var i = 0; i < route.length;) {
                var latlng = new google.maps.LatLng(route[i], route[i+1]);
                
                poly.getPath().push(latlng);

                var marker = new google.maps.Marker({
                    position: latlng,
                    title: 'hello',
                    map: map
                });
                markers.push(marker);
                i += 2;
            }

            var length = Number(0);
            for (i = 0; i < poly.getPath().getLength() - 1; i++) {
                length += 
                    Number(Utils.distHaversine(poly.getPath().getAt(i),
                                        poly.getPath().getAt(i + 1)));
            }

            document.getElementById("Current route length:").innerHTML =
                "Current route length: " + String(length) + "km";
    });
}

ControlHandlers.addNewRoute = function () {
    var elem = document.getElementById(button_add_name);
    var control = this;

    if (control.isBuildingRoute_) {
        elem.innerHTML = button_add_name;
        control.isBuildingRoute_ = false;
        google.maps.event.removeListener(add_event_handle);
        if (poly.getPath().getLength() > 1) {
            var minibus_name = prompt('Type name of new minibus:', '');

            if (minibus_name) {
                var path = poly.getPath();
                var res_string = '';

                res_string = path.getAt(0).lat().toString() + "," +
                        path.getAt(0).lng().toString();

                for (var i = 1; i < path.getLength(); i++) {
                    res_string += "," + path.getAt(i).lat().toString() + "," +
                        path.getAt(i).lng().toString();
                }

                $.post("add_route.php",
                      {name: minibus_name , route: res_string});

                Utils.clearMarkers();
                poly.getPath().clear();
                map.controls[google.maps.ControlPosition.LEFT_CENTER].clear();

                $.getJSON("get_route_num.php",
                function (event) {
                    route_num = event.result;
                    var minibusesLabelDiv = document.createElement('DIV');
                    new UIElements.commonLabel(minibusesLabelDiv, "List of minibuses",
                        'List of minibuses' + " (" + String(route_num) + ") " + ':');
                    map.controls[google.maps.ControlPosition.LEFT_CENTER].push(minibusesLabelDiv);
                    UIElements.getRouteNames();
                });
            }
            else
                alert("Strange minibus name");
        }
    }
    else {
        poly.getPath().clear();
        Utils.clearMarkers();
        add_event_handle =
            google.maps.event.addListener(map, 'click', ControlHandlers.addLatLng);
        control.isBuildingRoute_ = true;
        elem.innerHTML = button_finish_name;
    }
}

ControlHandlers.addLatLng = function (event) {
    var path = poly.getPath();

    path.push(event.latLng);

    var marker = new google.maps.Marker({
      position: event.latLng,
      title: '#' + path.getLength(),
      map: map
    });
    markers.push(marker);
}
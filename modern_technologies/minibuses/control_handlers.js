var button_finish_name = "Finish route";
var add_event_handle;
var poly, markers = [];

google.maps.MVCArray.prototype.clear = function (){
    for (var i = this.getLength(); i > 0; this.removeAt(--i));
}

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

ControlHandlers.addNewRoute = function () {
    var elem = document.getElementById(button_add_name);
    var control = this;

    if (control.isBuildingRoute_) {
        elem.innerHTML = button_add_name;
        control.isBuildingRoute_ = false;
        google.maps.event.removeListener(add_event_handle);

        var minibus_name = prompt('Type name of new minibus:', '');

        if (minibus_name) {
            var path = poly.getPath();
            var res_string = '';

            res_string = path.getLength().toString() + "d";

            for (var i = 0; i < path.getLength(); i++) {
                res_string += path.getAt(i).lat().toString() + "d" +
                    path.getAt(i).lng().toString() + "d";
            }

            var ul = document.getElementById("list2");
            var li = document.createElement("LI");
            li.innerHTML = res_string;
            ul.appendChild(li);

            $.post('add_route.php',
                  {var1: res_string, var2: minibus_name},
                    function(event) {});

            if (markers) {
                for (i in markers) {
                    markers[i].setMap(null);
                }
                markers = [];
            }

            poly.getPath().clear();
        }
        else
            alert("minibus_name");
    }
    else {
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
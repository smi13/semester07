var ui_index = Number(1);
var button_add_name = "New minibus";
var route_num = "";

UIElements = function () {
}

UIElements.initialize = function () {
    var homeControlDiv = document.createElement('DIV');
    new UIElements.commonButton(homeControlDiv, 
        ControlHandlers.goHome, "Go to Polytech", "Polytech");
    map.controls[google.maps.ControlPosition.TOP_RIGHT].push(homeControlDiv);

    var routeLengthDiv = document.createElement('DIV');
    new UIElements.commonLabel(routeLengthDiv, ControlHandlers.addNewRoute,
        "Current route length:", "Current route length:");
    map.controls[google.maps.ControlPosition.TOP_LEFT].push(routeLengthDiv);

    var addnewControlDiv = document.createElement('DIV');
    var button = new UIElements.commonButton(addnewControlDiv, ControlHandlers.addNewRoute,
        "Add new minibus route", button_add_name);
    button.isBuildingRoute_ = false;
    map.controls[google.maps.ControlPosition.RIGHT_CENTER].push(addnewControlDiv);

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

UIElements.updateRouteNames = function (route_names) {
    for (var i = 0; i < route_names.length; i++) {
        var div = document.createElement('DIV');
        new UIElements.commonButton(div, ControlHandlers.showRoute,
            route_names[i], route_names[i]);
        map.controls[google.maps.ControlPosition.LEFT_CENTER].push(div);
    }
}

UIElements.getRouteNames = function () {
    $.getJSON("get_route_names.php",
        function (event) {
            if (event.result != null) {
                var route_names = event.result.split(",");
                UIElements.updateRouteNames(route_names);
            }
    });
}

UIElements.commonButton = function (div, handler, title, name) {
  div.style.padding = '5px';

  var ui = document.createElement('DIV');
  ui.style.backgroundColor = 'white';
  ui.style.borderStyle = 'solid';
  ui.style.borderWidth = '1px';
  ui.style.cursor = 'pointer';
  ui.style.textAlign = 'center';
  ui.title = title;
  div.appendChild(ui);

  var text = document.createElement('DIV');
  text.id = name;
  text.style.fontFamily = 'Arial,sans-serif';
  text.style.fontSize = '12px';
  text.style.paddingLeft = '4px';
  text.style.paddingRight = '4px';
  text.innerHTML = name;
  ui.appendChild(text);

  div.index = ui_index;
  ui_index = ui_index + 1;
  google.maps.event.addDomListener(ui, 'click', handler);
}

UIElements.commonLabel = function (div, title, name) {
  div.style.padding = '5px';

  var ui = document.createElement('DIV');
  ui.style.backgroundColor = 'transparent';
  ui.style.borderStyle = 'solid';
  ui.style.borderWidth = '0px';
  ui.style.cursor = title;
  ui.style.textAlign = 'center';  
  div.appendChild(ui);

  var text = document.createElement('DIV');
  text.id = name;
  text.style.fontFamily = 'Arial,sans-serif';
  text.style.fontSize = '12px';
  text.style.paddingLeft = '4px';
  text.style.paddingRight = '4px';
  text.innerHTML = name;
  ui.appendChild(text);

  div.index = ui_index;
  ui_index = ui_index + 1;
}
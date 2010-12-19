var ui_index = Number(1);
var button_add_name = "New minibus";

UIElements = function () {
}

UIElements.initialize = function () {
    var homeControlDiv = document.createElement('DIV');
    new UIElements.commonButton(homeControlDiv, 
        ControlHandlers.goHome, "Go to Polytech", "Polytech");
    map.controls[google.maps.ControlPosition.TOP_RIGHT].push(homeControlDiv);

    var addnewControlDiv = document.createElement('DIV');
    var button = new UIElements.commonButton(addnewControlDiv, ControlHandlers.addNewRoute,
        "Add new minibus route", button_add_name);
    button.isBuildingRoute_ = false;
    map.controls[google.maps.ControlPosition.TOP_RIGHT].push(addnewControlDiv);

    var minibusesLabelDiv = document.createElement('DIV');
    new UIElements.minibusesLabel(minibusesLabelDiv);
    map.controls[google.maps.ControlPosition.TOP_LEFT].push(minibusesLabelDiv);
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

UIElements.minibusesLabel = function (div) {
  div.style.padding = '5px';

  var ui = document.createElement('DIV');
  ui.style.backgroundColor = 'transparent';
  ui.style.borderStyle = 'solid';
  ui.style.borderWidth = '0px';
  ui.style.cursor = 'hand';
  ui.style.textAlign = 'center';  
  div.appendChild(ui);

  var text = document.createElement('DIV');
  text.style.fontFamily = 'Arial,sans-serif';
  text.style.fontSize = '12px';
  text.style.paddingLeft = '4px';
  text.style.paddingRight = '4px';
  text.innerHTML = 'List of minibuses:';
  ui.appendChild(text);

  div.index = ui_index;
  ui_index = ui_index + 1;
}
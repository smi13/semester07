utils = function () {
}

utils.map = function(arr, func) {
    for (var i = 0; i < arr.length; i++) {
        func(arr[i]);
    }
}

utils.concat = function() {
    var string = "";

    utils.map(arguments,
        function(reg) {
            string += reg.source;
        });

    return new RegExp(string.replace(/\]\[/g, ""));
}

utils.makenot = function(reg) {
    return new RegExp(reg.source.replace("[", "[^"));
}
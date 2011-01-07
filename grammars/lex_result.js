
var resultTable;

lexResult = function () {
}

lexResult.clear = function () {
    lexResult.tokens = [];
    lexResult.variables = [];
    lexResult.constants = [];
}

lexResult.initialize = function () {
    lexResult.tokens = [];
    lexResult.variables = [];
    lexResult.constants = [];

    var divResult = document.getElementById("resultForm");

    resultTable = document.createElement("TABLE");

    resultTable.id = "resultTable";
    resultTable.setAttribute("border", "1");

    var tr = document.createElement("TR"), td;

    td = document.createElement("TD");
    td.appendChild(document.createTextNode("Tokens"));

    tr.appendChild(td);

    td = document.createElement("TD");
    td.appendChild(document.createTextNode("Identifiers"));

    tr.appendChild(td);

    td = document.createElement("TD");
    td.appendChild(document.createTextNode("Constants"));

    tr.appendChild(td);

    resultTable.appendChild(tr);

    divResult.appendChild(resultTable);
}

lexResult.addToken = function (token, state) {
    res = delta.endStates[state].process(token);

    if (res != null) {
        lexResult.tokens.push( [ delta.endStates[state].tokid, res ] );
        return true;
    }
    else
        return false;
}

lexResult.addVariable = function (token) {
    var ind = $.inArray(token, lexResult.variables);

    if (ind != -1)
        return new String("$" + ind);
    else {
        lexResult.variables.push(token);
        return new String("$" + (lexResult.variables.length - 1));
    }
}

lexResult.addConstant = function (token) {
    var ind = $.inArray(token, lexResult.constants);

    if (ind != -1)
        return new String("$" + ind);
    else {
        lexResult.constants.push(token);
        return new String("$" + (lexResult.constants.length - 1));
    }
}

lexResult.display = function () {
    
    var divResult = document.getElementById("resultForm");
    
    divResult.removeChild(resultTable);

    resultTable = document.createElement("TABLE");

    resultTable.id = "resultTable";
    resultTable.setAttribute("border", "1");
        
    var tr = document.createElement("TR"), td;

    td = document.createElement("TD");
    td.appendChild(document.createTextNode("Tokens"));

    tr.appendChild(td);

    td = document.createElement("TD");
    td.appendChild(document.createTextNode("Identifiers"));

    tr.appendChild(td);
    
    td = document.createElement("TD");
    td.appendChild(document.createTextNode("Constants"));

    tr.appendChild(td);

    resultTable.appendChild(tr);

    divResult.appendChild(resultTable);

    for (var i = 0; i < lexResult.tokens.length; i++) {
        tr = document.createElement("TR");

        td = document.createElement("TD");
        
        var string = "";
        
        switch (lexResult.tokens[i][0]) {
            case "TOK_ID":
                string = "Identifier";
                break;
            case "TOK_CONST":
                string = "Constant";
                break;
            case "TOK_OP":
                string = "Operator";
                break;
            case "TOK_BST":
                string = "BeginStatement";
                break;
            case "TOK_EST":
                string = "EndStatement";
                break;
            case "TOK_BB":
                string = "BeginBlock";
                break;
            case "TOK_EB":
                string = "EndBlock";
                break;
            default:
                break;
        }
        
        if (string == "")
            td.appendChild(document.createTextNode(lexResult.tokens[i][1]));
        else
            td.appendChild(document.createTextNode(string + "(" + lexResult.tokens[i][1] + ")"));
        tr.appendChild(td);

        td = document.createElement("TD");
        if (i >= lexResult.variables.length)
            td.appendChild(document.createTextNode(""));
        else
            td.appendChild(document.createTextNode(lexResult.variables[i]));
        tr.appendChild(td);

        td = document.createElement("TD");
        if (i >= lexResult.constants.length)
            td.appendChild(document.createTextNode(""));
        else
            td.appendChild(document.createTextNode(lexResult.constants[i]));
        tr.appendChild(td);

        resultTable.appendChild(tr);
    }
}

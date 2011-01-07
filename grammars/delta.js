delta = function (symbol, state) {
    for (var i = 0; i < delta.deltaStorage[state].length; i++)
        if (delta.deltaStorage[state][i][0].test(symbol))
            return delta.deltaStorage[state][i][1];

    return -1;
}

delta.initialize = function () {

    var just_any = /[\s]|[\S]/,
        comment = /#/,
        spacing = /[\s]/,
        digit = /[0-9]/,
        id_bsymbol = /(?=\w)(?=[^0-9])/,
        id_symbol = /[A-Za-z0-9_]/,
        operator = /[\+\-\*\/\=]/,
        begin_st = /\[/,
        end_st = /\]/,
        begin_block = /{/,
        end_block = /}/,
        not_comment = /(?=\s|\S)(?=[^#])/;

    delta.beginState = "q0";
    delta.deltaStorage = [];
    delta.endStates = [];

    delta.deltaStorage["q0"] = [ [spacing, "q0"],
                                 [id_bsymbol, "id"],
                                 [operator, "op"],
                                 [digit, "const"],
                                 [begin_st, "bst"],
                                 [end_st, "est"],
                                 [begin_block, "bb"],
                                 [end_block, "eb"],
                                 [comment, "comment"] ];

    delta.deltaStorage["id"] = [ [id_symbol, "id"],
                    [utils.makenot(id_symbol), "id_found"] ];

    delta.deltaStorage["const"] = [ [digit, "const"],
                       [utils.makenot(digit), "const_found"] ];

    delta.deltaStorage["op"] = [ [utils.makenot(operator), "op_found"] ];

    delta.deltaStorage["bst"] = [ [just_any,  "bst_found"] ];
    delta.deltaStorage["est"] = [ [just_any, "est_found"] ]
    delta.deltaStorage["bb"] = [ [just_any, "bb_found"] ];
    delta.deltaStorage["eb"] = [ [just_any, "eb_found"] ];

    delta.deltaStorage["comment"] = [ [ not_comment, "comment"], [comment, "comment_found"] ];

    delta.endStates["id_found"] = {tokid: "TOK_ID",
        process: lexResult.addVariable };

    delta.endStates["const_found"] = {tokid: "TOK_CONST",
        process: lexResult.addConstant };

    delta.endStates["op_found"] = {tokid: "TOK_OP",
        process: function (token) {
            return token;
        }};

    delta.endStates["bst_found"] = {tokid: "TOK_BST",
        process: function (token) {
            return token;
        }};
    delta.endStates["est_found"] = {tokid: "TOK_EST",
        process: function (token) {
            return token;
        }};
    delta.endStates["bb_found"] = {tokid: "TOK_BB",
        process: function (token) {
            return token;
        }};
    delta.endStates["eb_found"] = {tokid: "TOK_EB",
        process: function (token) {
            return token;
        }};

    delta.endStates["comment_found"] = {tokid: "TOK_COMMENT",
        process: function (token) {
            return null;
        }};
}

delta.isEndState = function (state) {
    if (delta.endStates[state])
        return true;
    else
        return false;
}

delta.addKeyword = function (keyword) {

    for (var i = 0; i < delta.deltaStorage["q0"].length; i++)
        if (delta.deltaStorage["q0"][i][1] == "id") {
            var reg_string = delta.deltaStorage["q0"][i][0].source, res_string;

            res_string = reg_string + "(?=[^" + keyword[0] + "])";
            delta.deltaStorage["q0"][i][0] = new RegExp(res_string);
        }

    delta.deltaStorage[delta.beginState].
        push([ new RegExp(keyword[0]), keyword + "_" + keyword[0] ]);

    for (i = 0; i < keyword.length - 1; i++) {
        delta.deltaStorage[keyword + "_" + keyword[i]] =
            [ [ new RegExp(keyword[i + 1]), keyword + "_" + keyword[i + 1] ] ];
        delta.deltaStorage[keyword + "_" + keyword[i]].
            push([ new RegExp("(?=\\w)(?=[^" + keyword[i + 1] + "])"), "id" ]);
    }

    delta.deltaStorage[keyword + "_" + keyword[keyword.length - 1]] =
        [ [ /\s|\[/, keyword + "_found" ] ];
    delta.deltaStorage[keyword + "_" + keyword[keyword.length - 1]].
        push([ new RegExp("\\w"), "id" ]);

    delta.endStates[keyword + "_found"] =
        {tokid: "TOK_" + String(keyword).toUpperCase(),
          process: function(token) {
              return token;
          }};
}
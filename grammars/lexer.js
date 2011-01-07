var delta = [];

var just_any = /[\s]|[\w]/,
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

delta["q0"] = [ [spacing, "q0"], 
                [id_bsymbol, "id"],
                [operator, "op"],
                [digit, "const"],
                [begin_st, "bst"],
                [end_st, "est"],
                [begin_block, "bb"],
                [end_block, "eb"],
                [comment, "comment"] ];

delta["id"] = [ [id_symbol, "id"],
                [utils.makenot(id_symbol), "id_found"] ];

delta["const"] = [ [digit, "const"],
                   [utils.makenot(digit), "const_found"] ];

delta["op"] = [ [utils.makenot(operator), "op_found"] ];

delta["bst"] = [ [just_any,  "bst_found"] ];
delta["est"] = [ [just_any, "est_found"] ]
delta["bb"] = [ [just_any, "bb_found"] ];
delta["eb"] = [ [just_any, "eb_found"] ];

delta["comment"] = [ [ not_comment, "comment"], [comment, "comment_found"] ];

end_states = [];

end_states["id_found"] = {tokid: "TOK_ID",
    process: function (token) {
        in_array = $.inArray(token, variables);

        if (in_array != -1)
            return new String("$" + in_array);
        else
        {
            variables[variables.length] = token;
            return new String("$" + (variables.length - 1));
        }    
    }};

end_states["const_found"] = {tokid: "TOK_CONST",
    process: function (token) {
        in_array = $.inArray(token, constants);

        if (in_array != -1)
            return new String("$" + in_array);
        else
        {
            constants[constants.length] = token;
            return new String("$" + (constants.length - 1));
        }
    }};

end_states["op_found"] = {tokid: "TOK_OP",
    process: function (token) {
        return token;
    }};

end_states["bst_found"] = {tokid: "TOK_BST",
    process: function (token) {
        return token;
    }};
end_states["est_found"] = {tokid: "TOK_EST",
    process: function (token) {
        return token;
    }};
end_states["bb_found"] = {tokid: "TOK_BB",
    process: function (token) {
        return token;
    }};
end_states["eb_found"] = {tokid: "TOK_EB",
    process: function (token) {
        return token;
    }};

end_states["comment_found"] = {tokid: "TOK_COMMENT",
    process: function (token) {
        return null;
    }};

var begin_state = "q0";

lexer = function () {    
}

lexer.addKeyword = function (keyword) {

    for (var i = 0; i < delta["q0"].length; i++)
        if (delta["q0"][i][1] == "id") {
            var reg_string = delta["q0"][i][0].source, res_string;
            
            res_string = reg_string + "(?=[^" + keyword[0] + "])";
            delta["q0"][i][0] = new RegExp(res_string);
        }

    delta[begin_state].
        push([ new RegExp(keyword[0]), keyword + "_" + keyword[0] ]);

    for (i = 0; i < keyword.length - 1; i++) {
        delta[keyword + "_" + keyword[i]] =
            [ [ new RegExp(keyword[i + 1]), keyword + "_" + keyword[i + 1] ] ];
        delta[keyword + "_" + keyword[i]].
            push([ new RegExp("(?=\\w)(?=[^" + keyword[i + 1] + "])"), "id" ]);
    }

    delta[keyword + "_" + keyword[keyword.length - 1]] =
        [ [ /\s|\[/, keyword + "_found" ] ];
    delta[keyword + "_" + keyword[keyword.length - 1]].
        push([ new RegExp("\\w"), "id" ]);

    end_states[keyword + "_found"] =
        {tokid: "TOK_" + String(keyword).toUpperCase(),
          process: function(token) {
              return token;
          }};
}

lexer.switchState = function(state, sym) {
    for (var i = 0; i < delta[state].length; i++)
        if (delta[state][i][0].test(sym)) 
            return delta[state][i][1];
    
    return -1;
}

lexer.analyze = function () {

    var code = editAreaLoader.getValue("codeTextArea"), bi;
    var cur_state = begin_state;
    tokens = [];
    variables = [];
    constants = [];
    code = code + " ";

    for (i = 0; i < code.length;) {

        var old_state = cur_state;
        cur_state = lexer.switchState(cur_state, code[i]);

        if (cur_state == -1)
            alert("OH SHI~");
        
        if (old_state == begin_state && cur_state != begin_state)
            bi = i;

        if (end_states[cur_state]) {

            var token = code.substr(bi, i - bi),
                res = end_states[cur_state].process(token);

            if (res != null)
                tokens[tokens.length] = [ end_states[cur_state].tokid, res ];
            else
                i++;

            cur_state = begin_state;
            continue;
        }
        i++;
    }
    
    alert(tokens);
    alert(variables);
    alert(constants);
}

lexer.getKey = function (event) {
    if (event.ctrlKey && event.shiftKey && event.charCode == 65)
        lexer.analyze();
}

lexer.initialize = function () {

    document.onkeypress = lexer.getKey;

    //Code
    codeForm = document.createElement("FORM");
    codeForm.method = "post";

    codeForm.setAttribute("Name", "codeForm");
    codeForm.id = "codeForm";

    textArea = document.createElement("TEXTAREA");
    textArea.setAttribute("rows", 30);
    textArea.setAttribute("cols", 150);
    textArea.setAttribute("name", "codeForm");
    textArea.setAttribute("spellcheck", "false");
    textArea.id = "codeTextArea";
    codeForm.appendChild(textArea);

    //Button
    button = document.createElement("BUTTON");
    button.id = "analyzeButton";
    button.onclick = lexer.analyze;
    
    button.appendChild(document.createTextNode("Analyze"));

    document.getElementById("codeForm").appendChild(codeForm);
    document.getElementById("codeForm").appendChild(button);

    editAreaLoader.init({
                id : "codeTextArea",		// textarea id
                syntax: "cpp",			// syntax to be uses for highgliting
                allow_toggle: false,
                start_highlight: true		// to display with highlight mode on start-up
        });
    
    lexer.addKeyword("while");
    lexer.addKeyword("if");
}

lexer = function () {    
}

lexer.analyze = function () {

    lexResult.clear();

    var code = editAreaLoader.getValue("codeTextArea"), bi;
    var cur_state = delta.beginState;
    code = code + " ";

    for (i = 0; i < code.length;) {
        var old_state = cur_state;
        cur_state = delta(code[i], cur_state);

        if (cur_state == -1)
            alert("OH SHI~");
        
        if (old_state == delta.beginState && cur_state != delta.beginState)
            bi = i;

        if (delta.isEndState(cur_state)) {
            var token = code.substr(bi, i - bi);
            
            if (!lexResult.addToken(token, cur_state))
                i++;

            cur_state = delta.beginState;
            continue;
        }
        i++;
    }
    
    lexResult.display();
    
/*    alert(lexResult.tokens);
    alert(lexResult.variables);
    alert(lexResult.constants);*/
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
    textArea.setAttribute("rows", 40);
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
                syntax: "lll",			// syntax to be uses for highgliting
                allow_toggle: false,
                font_size: 12,
                replace_tab_by_spaces: true,
                start_highlight: true,		// to display with highlight mode on start-up
                toolbar: "*"
        });

        editAreaLoader.setValue("codeTextArea",
        "   #Today you will learn how to swap 2 variables#\n" +
        "\n" +
        "orig_a =3\n" +
        "orig_b = 5\n" +
        "\n" +
        "a = orig_a b = orig_b\n" +
        "\n" +
        "#First way.#\n" +
        "" +
        "a = a +b\n" +
        "b= a-b\n" +
        "a = a-b\n" +
        "\n" +
        "#lets check the result#\n" +
        "\n" +
        "if [a = orig_a  b =ori_b]{}\n" +
        "\n" +
        "#2nd way#\n" +
        "a = orig_a b = orig_b\n" +
        "\n" +
        "c = a\n" +
        "a = b\n" +
        "b = c\n" +
        "\n" +
        "\n" +
        "1a = a\n" +
        "\n" +
        "#make some calculations *tribute to Mr.Adams #\n" +
        "UltimateAnswer42= [b - 1]*b*[a+b - 1]\n" +
        "\n" +
        "\n" +
        "while[1] {\n" +
        "\n" +
        "a = a / b }");


    lexResult.initialize();
    delta.initialize();
    
    delta.addKeyword("while");
    delta.addKeyword("if");
}
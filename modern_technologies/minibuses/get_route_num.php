<?php

    $link = mysql_connect("1", "1", "1") or die("Could not connect");
    if( !$link ) die( mysql_error() );

    $usertable = "minibuses";

    mysql_select_db("minibuses_db", $link);

    $query = "SELECT * FROM $usertable";

    $res = mysql_query($query) or die(mysql_error());

    $num = mysql_num_rows($res);

    mysql_free_result($res);

    echo json_encode(array("result" => $num));
?>

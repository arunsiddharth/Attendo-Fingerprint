<?php
    include("../include/config.php");
    include("../include/helpers.php");

    if($_SERVER['REQUEST_METHOD'] =="GET"){
        render("add_class_form.php",["title"=>"Add Class"]);
    }
    else if($_SERVER['REQUEST_METHOD']=="POST"){
        //Add to db
        $conn = dbconnect();
        if($conn->connect_error){
				die("Connection Failed".$conn->conncet_error);
		}
        else{
            $query = "INSERT INTO class(cname, tid) VALUES('".$_POST['class_name']."', ".$_SESSION['tid'].")";
            $result = $conn -> query($query);
            if(!$result){
                apologize("Same Class Name");
            }
            else{
                redirect("classes.php");
            }
        }
    }
?>
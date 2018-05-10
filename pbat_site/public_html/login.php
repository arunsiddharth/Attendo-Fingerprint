<?php

    //including models
    include("../include/config.php");
    include("../include/helpers.php");

    //after login control is sent back to classes.php
    if(!empty($_SESSION['tid'])){
         redirect('classes.php');
    }

    //in case of get request render to login form
    else if($_SERVER["REQUEST_METHOD"]=="GET"){
         render("login_form.php",["title" => "Log In"]);
    }

    //in case of post request
    else if($_SERVER["REQUEST_METHOD"]=="POST"){
         $conn = dbconnect();
            if($conn->connect_error){
				die("Connection Failed".$conn->conncet_error);
		    }
	    	else{

	        	$email_id = mysqli_real_escape_string($conn,$_POST['tname']);
	        	$password = mysqli_real_escape_string($conn,$_POST['password']);
	    		$query = "SELECT * FROM teacher WHERE tname='".$_POST['tname']."'";
	        	$results = $conn->query($query);
	    		if($results->num_rows > 0){
	            	$row = $results->fetch_assoc();
	            	if(!strcmp($password, $row['password'])){
                    $_SESSION['t_name']=$_POST['tname'];
	                	$_SESSION['tid']= $row['tid'];
	                	redirect('classes.php');
	            	}
	        		else{
	            		apologize("WRONG PASSWORD");
	        		}
	        	}
	        	else{
	            	apologize("WRONG DETAILS");
	        	}
	    	}
	 }
?>

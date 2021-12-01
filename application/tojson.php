<?php

    error_reporting(E_ALL);
    ini_set('display_errors', 1);

    include('dbcon.php');

    $android = strpos($_SERVER['HTTP_USER_AGENT'], "Android");

    if($_SERVER['REQUEST_METHOD'] == 'POST')
    {
        $ProductID=$_POST['ProductID'];

        if(empty($ProductID)){
            $errMSG = "insert ProductID";
        }

        if(!isset($errMSG))
        {
            try{
                $stmt = $con->prepare('INSERT INTO module(ProductID) VALUES(:ProductID)');
                $stmt->bindParam(':ProductID', $ProductID);

                if($stmt->execute())
                {
                    $successMSG = "appended";
                }
                else
                {
                    $errMSG = "append error";
                }
            } catch(PDOException $e){
                die("Database error: ".$e->getMessage());
            }
        }
    }
?>
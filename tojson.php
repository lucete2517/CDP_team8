<?php

    error_reporting(E_ALL);
    ini_set('display_errors', 1);

    include('dbcon.php');

    $android = strpos($_SERVER['HTTP_USER_AGENT'], "Android");

    if($_SERVER['REQUEST_METHOD'] == 'POST')
    {
        $MID=$_POST['MID'];

        if(empty($MID)){
            $errMSG = "insert MID";
        }

        if(!isset($errMSG))
        {
            try{
                $stmt = $con->prepare('INSERT INTO module4(MID) VALUES(:MID)');
                $stmt->bindParam(':MID', $MID);

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
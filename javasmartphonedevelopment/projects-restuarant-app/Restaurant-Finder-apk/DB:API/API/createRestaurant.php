<?php
 
/*
 * Following code will create a new restaurant row
 * All restaurant details are read from HTTP Post Request
 */
 
// array for JSON response
$response = array();
 
 //`restaurantID`, `name`, `type`, `bio`, `addressLine1`, `addressLine2`, `addressLine3`, `contactNumber`, `email`, `image`, `lat`, `lng`
// check for required fields
if (isset($_POST['name']) && isset($_POST['type']) && isset($_POST['bio']) && isset($_POST['addressLine1']) 
    && isset($_POST['addressLine2']) && isset($_POST['contactNumber']) && isset($_POST['email'])) {
 
    $name = $_POST['name'];
    $type = $_POST['type'];
    $bio = $_POST['bio'];
    $ad1 = $_POST['addressLine1'];
    $ad2 = $_POST['addressLine2'];
    $ad3 = $_POST['addressLine3'];
    $num = $_POST['contactNumber'];
    $email = $_POST['email'];
    $img = $_POST['image'];
    $lat = $_POST['lat'];
    $lng = $_POST['lng'];
    $url = $_POST['url'];
    $user_id = $_POST['user_id'];
 
    // include db connect class
    require_once('connection.php');
 
    // mysql inserting a new row
    $result = mysql_query("INSERT INTO Restaurant(name, type, bio, addressLine1, addressLine2, addressLine3, contactNumber, email, lat, lng, url, user_id) VALUES('$name', '$type', '$bio', '$ad1', '$ad2', '$ad3', '$num', '$email', '$lat', '$lng', '$url', '$user_id')");
 
    // check if row inserted or not
    if ($result) {
        // successfully inserted into database
        $response["success"] = 1;
        $response["message"] = "Restaurant successfully created.";
 
        // echoing JSON response
        echo json_encode($response);
    } else {
        // failed to insert row
        $response["success"] = 0;
        $response["message"] = "Oops! An error occurred.";
 
        // echoing JSON response
        echo json_encode($response);
    }
} else {
    // required field is missing
    $response["success"] = 0;
    $response["message"] = "Required field(s) is missing";
 
    // echoing JSON response
    echo json_encode($response);
}
?>
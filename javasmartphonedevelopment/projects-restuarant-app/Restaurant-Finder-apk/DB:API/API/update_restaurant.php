<?php header('Content-Type: application/json');
/*
 * Following code will list all the restaurants
 */
 
// array for JSON response
$response = array();

// include db connect class
require_once('connection.php');

//`restaurantID`, `name`, `type`, `bio`, `addressLine1`, `addressLine2`, `addressLine3`, `contactNumber`, `email`, `image`, `lat`, `lng`, `user_id`

// check for required fields
if (isset($_POST['restaurantID']) && isset($_POST['name']) && isset($_POST['type']) && isset($_POST['bio']) && isset($_POST['addressLine1']) 
    && isset($_POST['addressLine2']) && isset($_POST['contactNumber']) && isset($_POST['email'])) {
 
    $id = $_POST['restaurantID'];
    $name = $_POST['name'];
    $type = $_POST['type'];
    $bio = $_POST['bio'];
    $ad1 = $_POST['addressLine1'];
    $ad2 = $_POST['addressLine2'];
    $ad3 = $_POST['addressLine3'];
    $num = $_POST['contactNumber'];
    $email = $_POST['email'];
    $img = $_POST['image'];
    $url = $_POST['url'];

    // mysql update row with matched pid
    $result = mysql_query("UPDATE Restaurant SET name = '$name', type = '$type', bio = '$bio', addressLine1 = '$ad1', addressLine2 = '$ad2', addressLine3 = '$ad3', contactNumber = '$num', email = '$email', url = '$url' WHERE restaurantID = $id");
 
    // check if row inserted or not
    if ($result) {
        // successfully updated
        $response["success"] = 1;
        $response["message"] = "Restaurant successfully updated.";
 
        // echoing JSON response
        echo json_encode($response);
    } else {
 
    }
} else {
    // required field is missing
    $response["success"] = 0;
    $response["message"] = "Required field(s) is missing";
 
    // echoing JSON response
    echo json_encode($response);
}

?>
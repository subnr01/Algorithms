<?php
//api functions
include 'connection.php';

/**
* Storing new user
* returns user details
*/
function storeUser($username, $email, $password){

	$query = "INSERT INTO `user`(`userID`, `name`, `email`, `password`) ";
	$query .= " VALUES (NULL, '{$username}', '{$email}', '{$password}')";
	$result_set = mysql_query($query);
	
	// check for successful store
        if ($result_set) {
            // get user details
            $id = mysql_insert_id(); // last inserted id
            $result = mysql_query("SELECT * FROM `user` WHERE userID=".$id);
            // return user details
            return mysql_fetch_array($result);
        } else {
            return false;
        }
}

/**
* Get user by email and password
*/
function getUserByEmailAndPassword($email, $password){
	$query = "SELECT * FROM `user` WHERE email='{$email}' AND password='{$password}'";
	$result_set = mysql_query($query);
	
        // check for result
        $no_of_rows = mysql_num_rows($result_set);
        if ($no_of_rows > 0) {
            $result = mysql_fetch_array($result_set);
           
           // $salt = $result['salt'];
           // $encrypted_password = $result['encrypted_password'];
           // $hash = $this->checkhashSSHA($salt, $password);
            // check for password equality
          //  if ($encrypted_password == $hash) {
                // user authentication details are correct
          //      return $result;
          //  }
          return $result;
        } else {
            // user not found
            return false;
        }
}

/**
     * Check user is existed or not
     */
function isUserExisted($email) {
        $result = mysql_query("SELECT email FROM `user` WHERE email='{$email}'");
        $no_of_rows = mysql_num_rows($result);
        if ($no_of_rows > 0) {
            // user existed
            return true;
        } else {
            // user not existed
            return false;
        }
    }
?>
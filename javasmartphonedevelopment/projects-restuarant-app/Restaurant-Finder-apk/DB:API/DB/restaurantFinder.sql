-- phpMyAdmin SQL Dump
-- version 2.11.10
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Mar 27, 2014 at 12:57 AM
-- Server version: 5.1.49
-- PHP Version: 4.4.9

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `shady_madApi`
--

-- --------------------------------------------------------

--
-- Table structure for table `Deals`
--

CREATE TABLE `Deals` (
  `dealID` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` varchar(3) NOT NULL,
  `restaurantID` varchar(3) NOT NULL,
  `dealName` varchar(45) NOT NULL,
  `price` varchar(5) NOT NULL,
  `description` longtext NOT NULL,
  PRIMARY KEY (`dealID`),
  KEY `fk_Deals_Restaurant_idx` (`restaurantID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=19 ;

--
-- Dumping data for table `Deals`
--

INSERT INTO `Deals` (`dealID`, `user_id`, `restaurantID`, `dealName`, `price`, `description`) VALUES
(1, '1', '2', 'Early Bird', '16.50', 'Enjoy 6 Courses from our set menu for just 16.50. Available from 5pm til close'),
(12, '3', '17', 'Treat yourself', '75', 'Fantastic value at JUST 75 for 2 to dine with wine at Aqua Restaurant. \r\n\r\nServed Sunday to Friday: 5.30pm - 7.30pm and on Saturday: 5.30pm - 6.30pm. \r\nTreat yourself!'),
(13, '1', '17', 'Spring Market Menu', '29', '3 courses @ 29pp..\r\navailable all evening Tuesday to Thursday,\r\nup to 7pm on Friday and 6.30pm on saturday.'),
(17, '2', '4', 'test', '21', 'blah');

-- --------------------------------------------------------

--
-- Table structure for table `Restaurant`
--

CREATE TABLE `Restaurant` (
  `restaurantID` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `type` varchar(45) NOT NULL,
  `bio` longtext CHARACTER SET latin1 COLLATE latin1_bin NOT NULL,
  `addressLine1` varchar(45) NOT NULL,
  `addressLine2` varchar(45) NOT NULL,
  `addressLine3` varchar(45) NOT NULL,
  `contactNumber` varchar(45) NOT NULL,
  `email` varchar(45) NOT NULL,
  `image` varchar(45) DEFAULT NULL,
  `lat` decimal(18,12) DEFAULT NULL,
  `lng` decimal(18,12) DEFAULT NULL,
  `url` varchar(75) DEFAULT NULL,
  `user_id` varchar(4) NOT NULL,
  PRIMARY KEY (`restaurantID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=23 ;

--
-- Dumping data for table `Restaurant`
--

INSERT INTO `Restaurant` (`restaurantID`, `name`, `type`, `bio`, `addressLine1`, `addressLine2`, `addressLine3`, `contactNumber`, `email`, `image`, `lat`, `lng`, `url`, `user_id`) VALUES
(2, 'Cornstore', 'seafood', 0x4173206f6e65206f66204c696d657269636b277320626573742072657374617572616e74732c207765206f6666657220612063617375616c2c207761726d20616e64206c6976656c792064696e696e6720657870657269656e636520696e2061204d616e68617474616e207374796c652073657474696e67206f76657220746872656520666c6f6f72732c20636f6d706c6574652077697468206120756e697175652077696e6520616e6420636f636b7461696c206261722c20707269766174652064696e696e6720726f6f6d20616e6420636f6e74656d706f7261727920736d6f6b696e6720617265612e, '19 Thomas street', 'limerick', '', '0865258885', 'reservations@cornstorelimerick.com', NULL, 52.662615000000, -8.625298000000, 'http://www.cornstorerestaurantslimerick.ie/', '1'),
(4, 'azur blue', 'seafood', 0x746573742062696f, '8 Georges Quay', 'Limerick', '', '082-112233', 'info@azurlimerick.ie  ', NULL, 52.667128000000, -8.622843000000, 'http://www.azurcafebrasserie.ie/menus.html', '2'),
(17, 'Glasshouse Restaurant', 'Bistro', 0x57656c636f6d6520746f2074686520476c617373686f7573652052657374617572616e7420696e204c696d657269636b2043697479206f7665726c6f6f6b696e6720746865205269766572205368616e6e6f6e2e0d0a0d0a4452494e4b2057696e652c20436f636b7461696c732c20437261667420426565720d0a4d494e474c4520696e20746865206c6f756e6765206265666f72652064696e696e67206f7220626f6f6b2074686520737061636520707269766174656c7920666f7220616e792063656c6562726174696f6e2e0d0a52454c4158206f6e206f7572206f7574646f6f72207465727261636520696e207468652073756e20287768656e206974206170706561727321290d0a44494e45206f6e2061206d656e752077686963682063656c65627261746573207468652062657374206f66206c6f63616c2049726973682070726f647563652c20646f776e737461697273206f7220757020696e206f757220676c6173732077616c6c65642064696e696e672073706163652e, 'Riverpoint ', 'Limerick', '', '061 469000', 'info@glasshouserestaurant.ie', NULL, 52.662147000000, -8.633018000000, 'http://www.glasshouserestaurant.ie/pdf/glasshouse-food_menu.com', '3'),
(18, 'copper and spice', 'Thai', 0x4f75722061696d20697320746f206f6666657220796f7520666972737420636c61737320496e6469616e202620546861692063756973696e652e20416c6c206f66206f7572206469736865732061726520636f6f6b6564206163636f7264696e6720746f20796f757220707265666572656e6365202d206d696c64206d656469756d206f7220686f742e, '2 Cornmarket Row', 'Limerick', '', '061 313620', 'reservations@copperandspice.com', NULL, 52.664099000000, -8.622676000000, 'http://www.copperandspice.com/menu.htm', '3'),
(20, 'Chocolat ', 'Fusion', 0x44657369676e656420666f72207468652062757379206c6966657374796c65206f66206120636974792c2043686f636f6c61742072657374617572616e74206164647320746f207468652063656e747265206f66204c696d657269636b2074686520696465616c2076656e756520666f72206120636f72706f72617465206c756e63682c2061207361766f72792061667465726e6f6f6e20627265616b206f722061207375636365737366756c2070617274792e, '109, O''Connell Street', 'Limerick', '', '061-609709', 'info@chocolat.com', NULL, 52.662199000000, -8.628598000000, 'http://www.chocolatrestaurant.ie/lunch.html', '1'),
(21, 'Freddy''s Bistro', 'Irish', 0x416c6c206f7572206469736865732061726520636f6f6b656420746f206f726465722c207468657265666f72652077652063616e20636174657220666f7220616e79207370656369616c20646965746172792072656571756972656d656e74732e2077652062616b6520616c6c206f7572206f776e2062726561647320616e6420646573736572747320616e642063616e20616c736f20636174657220666f7220636f656c696163732061732077652062616b6520776865617420667265652062726561642e, 'Theatre Lane', 'Lower Glentworth Street', 'Limerick', '061 418749', 'info@feddysbristro.com', NULL, 52.661340000000, -8.630229000000, 'http://www.freddysbistro.com/menus', '2'),
(22, 'hamptons grill', 'grill', 0x626c6168, 'henry street', 'limerick', '', '011236523', 'rg@gmail.com', NULL, 52.663347300000, -8.629037200000, 'http://google.com', '2');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `userID` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `email` varchar(45) NOT NULL,
  `password` varchar(45) NOT NULL,
  PRIMARY KEY (`userID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=8 ;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`userID`, `name`, `email`, `password`) VALUES
(1, 'Robert Mc Namara', 'rm2948@ymail.com', '1234'),
(2, 'Rob1', 'email1', 'pass1'),
(3, 'rob2', 'email2', 'pass2'),
(4, 'prateek', 'prateekdevisingh@gmail.com', 'pinkuchaudhary'),
(5, 'Lucky 7', 'johnk@wim.com', '1234'),
(6, 'John Kufa', 'john.kufa@gmail.com', 'kumbirai7'),
(7, 'aalishan', 'aalishan@tresktechnologies.com', '30130');

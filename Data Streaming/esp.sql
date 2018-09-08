-- phpMyAdmin SQL Dump
-- version 4.8.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Sep 08, 2018 at 08:28 PM
-- Server version: 10.1.34-MariaDB
-- PHP Version: 7.2.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `esp`
--

-- --------------------------------------------------------

--
-- Table structure for table `esp`
--

CREATE TABLE `esp` (
  `Time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `Heading` decimal(5,2) NOT NULL,
  `Gx` decimal(5,2) NOT NULL,
  `Gy` decimal(5,2) NOT NULL,
  `Gz` decimal(5,2) NOT NULL,
  `Ax` decimal(5,2) NOT NULL,
  `Ay` decimal(5,2) NOT NULL,
  `Az` decimal(5,2) NOT NULL,
  `Mx` decimal(5,2) NOT NULL,
  `My` decimal(5,2) NOT NULL,
  `Mz` decimal(5,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `esp`
--

INSERT INTO `esp` (`Time`, `Heading`, `Gx`, `Gy`, `Gz`, `Ax`, `Ay`, `Az`, `Mx`, `My`, `Mz`) VALUES
('2018-09-08 18:22:36', '35.25', '12.31', '123.42', '41.41', '123.41', '56.43', '51.51', '51.52', '52.41', '23.52'),
('2018-09-08 18:22:50', '35.25', '12.31', '123.42', '41.41', '123.41', '56.43', '51.51', '51.52', '52.41', '23.52'),
('2018-09-08 18:22:50', '35.25', '12.31', '123.42', '41.41', '123.41', '56.43', '51.51', '51.52', '52.41', '23.52');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

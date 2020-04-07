
-- Setup that requires the presence of SHA256 functionality
DROP USER IF EXISTS 'csha2p_user'@'localhost';
CREATE USER 'csha2p_user'@'localhost' IDENTIFIED WITH 'caching_sha2_password';
ALTER USER 'csha2p_user'@'localhost' IDENTIFIED BY 'csha2p_password';
GRANT ALL PRIVILEGES ON awesome.* TO 'csha2p_user'@'localhost';

DROP USER IF EXISTS 'csha2p_empty_password_user'@'localhost';
CREATE USER 'csha2p_empty_password_user'@'localhost' IDENTIFIED WITH 'caching_sha2_password';
ALTER USER 'csha2p_empty_password_user'@'localhost' IDENTIFIED BY '';
GRANT ALL PRIVILEGES ON awesome.* TO 'csha2p_empty_password_user'@'localhost';

-- This one is used for unknown authentication plugin tests
DROP USER IF EXISTS 'sha2p_user'@'localhost';
CREATE USER 'sha2p_user'@'localhost' IDENTIFIED WITH 'sha256_password';
ALTER USER 'sha2p_user'@'localhost' IDENTIFIED BY 'sha2p_password';
GRANT ALL PRIVILEGES ON awesome.* TO 'sha2p_user'@'localhost';

FLUSH PRIVILEGES;
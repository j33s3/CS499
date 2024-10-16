import mysql from'mysql2/promise';


/** rerurns the connection to the database
 * 
 * @returns mysql.connection
 */
export const createConnection = async () => {
    
    //creates the connection with the folowing env variables
    const connection = await mysql.createConnection({
        host: process.env.DB_HOST,
        user: process.env.DB_USER,
        password: process.env.DB_PASSWORD,
    });

    console.log('Connected to MySQL');

    // sends a query to create the database if it does not exist
    await connection.query(`CREATE DATABASE IF NOT EXISTS \`${process.env.DB_NAME}\``);
    console.log('Database checked/created successfully');

    // connects to the the database and ensures the collection is present
    await connection.changeUser({ database: process.env.DB_NAME});
    const createTableQuery = `
    CREATE TABLE IF NOT EXISTS routes (
        id INT AUTO_INCREMENT PRIMARY KEY,
        driver VARCHAR(255) NOT NULL,
        truck_model VARCHAR(255) NOT NULL,
        truck_make VARCHAR(255) NOT NULL,
        truck_year INT,
        start_location VARCHAR(255),
        end_location VARCHAR(255)
        );
    `;
    await connection.query(createTableQuery);
    console.log('Table checked/created successfully');

    return connection;

};
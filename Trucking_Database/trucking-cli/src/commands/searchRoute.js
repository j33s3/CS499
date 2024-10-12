import { Command } from 'commander';
import { input } from '@inquirer/prompts';

// imports functions from helper files
import { createConnection } from '../../config/dbConfig.js';
import { listModels } from '../utils/validation.js';
import { validateSearch } from '../utils/validation.js';


//initializes a new command
const searchRoutesCommand = new Command('search-routes');

//contents of the command
searchRoutesCommand
    .description('Searching route documents (Admin only)')
    .action(async () => {

        //establish connection to the database
        const connection = await createConnection();

        // confirm that the user has a role of admin
        const role = await input({message: 'Enter your role (user/Admin)'});

        if (role.toLowerCase() === 'admin') {
            const searchFor = await input({
                message: 'Enter item to search for',
                validate: validateSearch});

                //searches for the document
            try {

                let query;

                //if search is a numbe (id or truck year)
                if (!isNaN(searchFor)) {
                    query = `
                            SELECT * FROM routes
                            WHERE id = ? OR truck_year = ?`;
                    const [rows] = await connection.query(query, [searchFor, searchFor]);

                    console.log("Results:", rows);
                    return;
                }

                //if the search contains a truck make
                else if (listModels.includes(searchFor.toUpperCase())) {
                    query = `
                        SELECT * FROM routes
                        WHERE truck_make LIKE ?`;
                    const searchLike = `${searchFor}`;
                    const [rows] = await connection.query(query, [searchLike, searchLike]);
                    console.log("Results:", rows);
                    return;
                }

                //if the search contains only letters (driver, begin/end locations)
                else if (/^[a-zA-Z\s]+$/.test(searchFor)) {
                
                    query = `
                            SELECT * FROM routes
                            WHERE driver LIKE ?
                            OR start_location LIKE ?
                            OR end_location LIKE ?
                            `;

                    const searchLike = `%${searchFor}%s`;
                    const [rows] = await connection.query(query, [searchLike, searchLike, searchLike]);

                    //if no data is found then skip the print statement
                    if(rows.length > 0){
                        console.log("Results", rows);
                        return;
                    }

                }
                
                //finally if the search contains letters and number (model, start/end locations)
                    query = `
                            SELECT * FROM routes
                            WHERE truck_model LIKE ?
                            OR start_location LIKE ?
                            OR end_location LIKE ? 
                            `;
                    const searchLike = `%${searchFor}%`;
                    const [rows] = await connection.query(query, [searchLike, searchLike, searchLike]);

                    //if no data is found then skip the print statement
                    if(rows.length > 0) {
                        console.log("Results", rows);
                        return;
                    }

                    //print could not be found
                    console.log("Could not find item");
                    return;
            } 
            //catch any errors
            catch(error) {
                console.log("An error occured when processing your search " + error);
            } 
            //terminate the command
            finally {
                connection.end();
                process.exit(0);
            }
        }
    });

export default searchRoutesCommand;
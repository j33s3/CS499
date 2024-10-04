import { Command } from 'commander';
import { input } from '@inquirer/prompts';
import { createConnection } from '../../config/dbConfig.js';
import { listModels } from '../utils/validation.js';
import { validateSearch } from '../utils/validation.js';

const searchRoutesCommand = new Command('search-routes');

searchRoutesCommand
    .description('Searching route documents (Admin only)')
    .action(async () => {
        const connection = await createConnection();

        const role = await input({message: 'Enter your role (user/Admin)'});

        if (role.toLowerCase() === 'admin') {
            const searchFor = await input({
                message: 'Enter item to search for',
                validate: validateSearch});

            try {

                let query;
                if (!isNaN(searchFor)) {
                    query = `
                            SELECT * FROM routes
                            WHERE id = ? OR truck_year = ?`;
                    const [rows] = await connection.query(query, [searchFor, searchFor]);
                    console.log("Here1");

                    console.log("Results:", rows);
                    return;
                }
                else if (listModels.includes(searchFor.toUpperCase())) {
                  
                    query = `
                        SELECT * FROM routes
                        WHERE truck_make LIKE ?`;
                    const searchLike = `${searchFor}`;
                    const [rows] = await connection.query(query, [searchLike, searchLike]);
                    console.log("Results:", rows);
                    return;
                }
                else if (/^[a-zA-Z\s]+$/.test(searchFor)) {
                
                    query = `
                            SELECT * FROM routes
                            WHERE driver LIKE ?
                            OR start_location LIKE ?
                            OR end_location LIKE ?
                            `;

                    const searchLike = `%${searchFor}%s`;
                    const [rows] = await connection.query(query, [searchLike, searchLike, searchLike]);
                    if(rows.length > 0){
                        console.log("Results", rows);
                        return;
                    }

                }
                
                    query = `
                            SELECT * FROM routes
                            WHERE truck_model LIKE ?
                            OR start_location LIKE ?
                            OR end_location LIKE ? 
                            `;
                    const searchLike = `%${searchFor}%`;
                    const [rows] = await connection.query(query, [searchLike, searchLike, searchLike]);
                    if(rows.length > 0) {
                        console.log("Results", rows);
                        return;
                    }
                    console.log("Could not find item");
                    return;
            } catch(error) {
                console.log("An error occured when processing your search " + error);
            } finally {
                connection.end();
                process.exit(0);
            }
        }
    });

export default searchRoutesCommand;
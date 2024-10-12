import dotenv from 'dotenv';
dotenv.config();

import { Command } from 'commander';

// initial command
const program = new Command();

//imports our commands
import viewRoutesCommand from './src/commands/viewRoutes.js';
import deleteRouteCommand from './src/commands/deleteRoute.js';
import addRouteCommand from './src/commands/addRoute.js';
import searchRoutesCommand from './src/commands/searchRoute.js';

//processes our commands
program.addCommand(addRouteCommand);
program.addCommand(viewRoutesCommand);
program.addCommand(deleteRouteCommand);
program.addCommand(searchRoutesCommand);

//parses the arguments
program.parse(process.argv);
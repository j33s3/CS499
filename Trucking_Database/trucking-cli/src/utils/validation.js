import axios from 'axios';

//=========================================================================================
// Stores valid truck makes
//=========================================================================================

export const listModels = ['VOLVO', 'FREIGHTLINER', 'KENWORTH', 'PETERBILT', 'INTERNATIONAL', 'WESTERN STAR', 'MACK', 'SCANIA', 'MAN', 'IVECO', 'STERLING', 'ISUZU'];


//=========================================================================================
// Stores valid truck makes
//=========================================================================================

/** Checks that the driver contains no numbers or special characters
 * Also ensures that the name is longer than 2 characters and contains under 2 spaces
 * This allows people to enter first and last if wanting to.
 * 
 * @param string name 
 * @returns 
 */
export async function validateDriverName(name) {
    const validChars = /^[A-Za-z\s\-]+$/;

    //ensures the length is valid
    if(!name || name.length < 2 || name.length > 50) {
        return 'Driver name must be at least 2 characters long.';
    }

    //ensures the name is only letters
    if(!name.match(validChars)) {
        return 'A name cannot contain numbers or special characters';
    }
    //ensures there are no more than 2 spaces in the string
    const spaceCount = (name.match(/ /g) || []).length;
    if(spaceCount > 2) {
        return 'Driver name must be either first, first and last, or first middle and last';
    }

    return true;
};


/** This validates that the model does not contain special characters
 * also ensures that model is within lengths 2 to 30
 * 
 * @param string model 
 * @returns 
 */
export function validateTruckModel(model) {
    const validChars = /^[A-Za-z0-9\s\-]/;

    // ensures the length is valid
    if(!model || model.lenth < 2 || model.length > 30) {
        return 'Truck Model must be at least 2 characters long and must not exceed 30 characters';
    }

    // ensures the model does not contain special characters
    if(!model.match(validChars)) {
        return 'The model must not contain special characters';
    }
    return true;
}

/** This ensures that the truck make is within a list of options
 * 
 * @param string make 
 * @returns 
 */
export function validateTruckMake(make) {

    //Ensures that the make is of a valid brand
    if (!listModels.includes(make.toUpperCase())){
        return 'Truck manufacturer is not valid.';
    }
    return true;
}

/** This validates that the truck year is within 1900 to 2025
 * It also ensures that the input is a number
 * 
 * @param integer year 
 * @returns 
 */
export function validateTruckYear(year) {
    const currentYear = new Date().getFullYear();
    
    //ensures that the input year is within 1900 to 2025
    if(isNaN(year) || year < 1900 || year > (currentYear + 1)) {
        return `Truck year must be between 1900 and ${currentYear + 1}`;
    }
    return true;
}

/** This ensures that the zip exists
 * 
 * @param integer startZIP 
 * @returns 
 */
export async function validateStartingZIP(startZIP) {
    const url = `https://api.zippopotam.us/us/${startZIP}`;

    // tries to make connection to the api
    try {

        const response = await axios.get(url);

        //if the status is not 200 or no api data is present return error
        if(response.status === 200 && response.data.places && response.data.places.length > 0) {
            return true;
        } else {
            return "invalid zipcode";
        }
        
    } catch (error) {
        //if there is an error connecting to the database
        return "invalid zipcode";
    }   
}

/** This ensures that the end zip code is not the same as the start
 * It also ensures that the zipcode exists
 * 
 * @param integer endZIP 
 * @param integer startZIP 
 * @returns 
 */
export async function validateFinalZIP(endZIP, startZIP) {
    const url = `https://api.zippopotam.us/us/${endZIP}`;

    //if the zip codes are the same
    if(startZIP === endZIP) {
        return 'Error: Start and End locations are the same';
    }

    //try to establish connection
    try {

        const response = await axios.get(url);

        //If status is not 200 and data is not present then return invalid zipcode
        if(response.status === 200 && response.data.places && response.data.places.length > 0) {
            return true;
        } else {
            return "invalid zipcode";
        }

    } catch (error) {
        //if connection cannot be made
        return "invalid zipcode";
    }
}


//=========================================================================================
// Valid index for removal
//=========================================================================================

/** This ensures that the number contains numerical characters
 * 
 * @param integer index 
 * @returns 
 */
export async function validateIndexRemoval(index) {
    const validChars = /^[0-9]+$/;
    
    //ensures that the index is a number
    if(!index.match(validChars)){
        return 'Invalid index format';
    }
    return true;
}
//=========================================================================================
// Validates the search characters
//=========================================================================================

/** This ensures that the search string is free of potential breaching characters
 * 
 * @param string search 
 * @returns 
 */
export async function validateSearch(search) {
    const forbiddenChars = /['";\(\)\{\}\[\]\<\>\|&!~`\\\/@#\$%\^*\+=]|--/;

    //ensures that the search does not contain characters above
    if(forbiddenChars.test(search)) {
        return 'Invalid characters in the search'
    }
    return true;

}


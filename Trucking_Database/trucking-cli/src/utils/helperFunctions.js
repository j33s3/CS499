import axios from 'axios'

/** get the location in string format
 * (*city*, *state* *zip*)
 * 
 * @param integer zipcode 
 * @returns 
 */
export async function getLocation(zipcode) {
    const url = `https://api.zippopotam.us/us/${zipcode}`;
    
    //try to establish connection
    try {
        const response = await axios.get(url);

        //if connection established
        if (response.status === 200 && response.data.places.length > 0) {

            //scan for city and state
            const city = response.data.places[0]['place name'];
            const state = response.data.places[0]['state abbreviation'];

            //add values into a string
            const fullAddress = `${city}, ${state} ${zipcode}`;

            return fullAddress;
        } 
        // error if not found
        else {
            return 'Invalid Zipcode';
        }
    } 
    //catch errors that are thrown
    catch (error) {
        console.error('Error fetching location:', error);
        return 'Invalid Zipcode';
    }
}

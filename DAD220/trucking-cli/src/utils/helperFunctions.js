import axios from 'axios'



export async function getLocation(zipcode) {
    const url = `https://api.zippopotam.us/us/${zipcode}`;
    
    try {
        const response = await axios.get(url);

        if (response.status === 200 && response.data.places.length > 0) {
            const city = response.data.places[0]['place name'];
            const state = response.data.places[0]['state abbreviation'];
            const fullAddress = `${city}, ${state} ${zipcode}`;
            return fullAddress;
        } else {
            return 'Invalid Zipcode';
        }
    } catch (error) {
        console.error('Error fetching location:', error);
        return 'Invalid Zipcode';
    }
}

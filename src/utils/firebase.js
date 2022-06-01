import { initializeApp } from 'firebase/app';
import { getDatabase } from "firebase/database";

const firebaseConfig = {
    apiKey: "AIzaSyBVFYTEEjpz7QiI-ezzNb87GeWnyk4imMw",
    authDomain: "embededlab-aa618.firebaseapp.com",
    databaseURL: "https://embededlab-aa618-default-rtdb.firebaseio.com",
    projectId: "embededlab-aa618",
    storageBucket: "embededlab-aa618.appspot.com",
    messagingSenderId: "956472249018",
    appId: "1:956472249018:web:bcfa39421d30423f529083",
    measurementId: "G-23F26981WN"
};


const app = initializeApp(firebaseConfig);

// Get a reference to the database service
const database = getDatabase(app);

export default database;
// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
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

// Initialize Firebase
const app = initializeApp(firebaseConfig);

export default firebase;
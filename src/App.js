import './App.css';
import { useState, useEffect} from 'react'
import database from './utils/firebase'
import { ref, onValue, set, get, child} from 'firebase/database'



function delay(time) {
    return new Promise(resolve => setTimeout(resolve, time));
}

function App() {
    const [count, setCount] = useState(0);
    const [isOpen, setIsOpen] = useState(false);
    const [temp, setTemp] = useState(0);
    const [enter, setEnter] = useState(true);
    const [over, setOver] = useState(false);    

    useEffect(() => {
         // temp
        let tempQuery = ref(database, 'Temp');
        onValue(tempQuery, (snapshot) => {
            const currentTemp = snapshot.val();
            setTemp(currentTemp);
        });
        
        // door status
        let doorStatusQuery = ref(database, 'Door_status');
        onValue(doorStatusQuery, (snapshot) => {
            const currentDoorStatus = snapshot.val();
            if (currentDoorStatus === 0){
                // normal case : person with normal temperature enter the building
                setIsOpen(currentDoorStatus).then(() => 
                    setEnter(currentDoorStatus).then(() =>
                        delay(1000))
                );
                                             
            }else{
                if (currentDoorStatus === 2){
                    // overheat case : person with temperature > 30.5 try to enter
                    setIsOpen(false).then(() => 
                        setEnter(false).then(() =>
                            setOver(true).then(() =>
                                delay(1000))
                    ));

                }else{
                    // door close : no person try to enter 
                    setIsOpen(currentDoorStatus);
                    setEnter(currentDoorStatus);
                }                
            }
        });

        // people
        let peopleCountQuery = ref(database, 'people');
        onValue(peopleCountQuery, (snapshot) => {
            const currentPeopleCount = snapshot.val();
            setCount(currentPeopleCount);
        });

    }, [count, temp, isOpen, enter, over]);

    return (
        <div className="App">
        <div className='container'>
            <div className='top'>
            <div style={{ display: 'flex', flexDirection: 'row', padding: '0', margin: '0' }}>
                <p className="status">Door Status: </p>
                {isOpen ? <p className='open'>Open</p> : <p className='closed'>Closed</p>}
            </div>
            {enter && <p className="alert">A person entered with temperature of {temp} degrees</p>}
            {over && <p className="alert">A person with over temperature of {temp} tried to enter</p>}
            </div>
            <div className="bottom">
            <p className="count">
                Number of people in the building: {count}
            </p>
            </div>
        </div>
        </div>
    );
}

export default App;

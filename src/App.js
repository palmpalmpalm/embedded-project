import './App.css';
import { useState } from 'react'

function App() {
  const [count, setCount] = useState(100);
  const [isOpen, setIsOpen] = useState(true);
  const [temp, setTemp] = useState(0);
  const [enter, setEnter] = useState(true);
  const [exit, setExit] = useState(false);
  return (
    <div className="App">
      <div className='container'>
        <div className='top'>
          <div style={{ display: 'flex', flexDirection: 'row', padding: '0', margin: '0' }}>
            <p className="status">Door Status: </p>
            {isOpen ? <p className='open'>Open</p> : <p className='closed'>Closed</p>}
          </div>
          {enter && <p className="alert">A person entered with temperature of {temp} degrees</p>}
          {exit && <p className="alert">A person exited</p>}
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

import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import 'bootstrap/dist/css/bootstrap.min.css';
import NavigationBar from './components/NavigationBar';

function Square(props) {
  return (
    <button className='square' onClick={props.onClick}>
      {props.value}
    </button>
  );
}

class Board extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      squares: Array(9).fill(null),
      xIsNext: true,
    };
  }

  handleClick(i) {
    const squares = this.state.squares.slice();
    squares[i] = this.state.xIsNext ? 'X' : 'O';
    this.setState({
      squares: squares,
      xIsNext: !this.state.xIsNext,
    });
  }

  renderSquare(i) {
    return (
      <Square
        value={this.state.squares[i]}
        onClick={() => this.handleClick(i)}
      />
    );
  }

  render() {
    const status = 'Next player: ' + (this.state.xIsNext ? 'X' : 'O');

    return (
      <div>
        <div className='status'>{status}</div>
        <div className='board-row'>
          {this.renderSquare(0)}
          {this.renderSquare(1)}
          {this.renderSquare(2)}
        </div>
        <div className='board-row'>
          {this.renderSquare(3)}
          {this.renderSquare(4)}
          {this.renderSquare(5)}
        </div>
        <div className='board-row'>
          {this.renderSquare(6)}
          {this.renderSquare(7)}
          {this.renderSquare(8)}
        </div>
      </div>
    );
  }
}

class Game extends React.Component {
  render() {
    return (
      <div className='game'>
        <div className='game-board'>
          <Board />
        </div>
        <div className='game-info'>
          <div>{/* status */}</div>
          <ol>{/* TODO */}</ol>
        </div>
      </div>
    );
  }
}

class Body extends React.Component {
  constructor(props) {
    super(props);

    this.handleRegister = this.handleRegister.bind(this);
    this.handleLogin = this.handleLogin.bind(this);
    this.handleLogout = this.handleLogout.bind(this);
    this.handleButtonClick = this.handleButtonClick.bind(this);

    this.state = {
      isLogedIn: false,
      userLogin: null,
      userToken: null,
      counter: 0,
    };
  }

  async handleRegister(login, password) {
    return fetch('http://127.0.1.1:6502/api/registration', {
      method: 'POST',
      headers: {
        Accept: 'application/json',
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        'login': login,
        'password': password
      })
    }).then(res => {
      return res.status;
    });
  }

  async handleLogin(login, password) {
    return fetch('http://127.0.1.1:6502/api/login', {
      method: 'POST',
      headers: {
        Accept: 'application/json',
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        'login': login,
        'password': password
      })
    }).then(res => {
      if (res.ok) {
        res.json().then(body => {
          this.setState({
            isLogedIn: true,
            userLogin: login,
            userToken: body['token'],
          })
        });
      }
      return res.status;
    });
  }

  async handleLogout() {
    return fetch('http://127.0.1.1:6502/api/logout', {
      method: 'POST',
      headers: {
        Accept: 'application/json',
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        'token': this.state.userToken,
      })
    }).then(res => {
      if (res.ok) {
        this.setState({
          isLogedIn: false,
          userLogin: '',
          userToken: '',
        });
      }
      return res.status;
    });
  }

  handleButtonClick() {
    this.setState({ counter: this.state.counter + 1 });
  }

  render() {
    return (
      <div>
        <NavigationBar
          isLogedIn={this.state.isLogedIn}
          userLogin={this.state.userLogin}
          handleRegister={this.handleRegister}
          handleLogin={this.handleLogin}
          handleLogout={this.handleLogout}
        />
        <button onClick={this.handleButtonClick}>Update</button>
        <Game />
        <Game />
        <Game />
        <Game />
        <Game />
        <Game />
        <Game />
        <Game />
        <Game />
        <Game />
        <Game />
      </div>
    );
  }
}

// ========================================

ReactDOM.render(
  <Body />,
  document.getElementById('root')
);

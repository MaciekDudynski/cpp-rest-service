import React from 'react';
import {
  Collapse,
  Navbar,
  NavbarToggler,
  NavbarBrand,
  Nav,
  NavItem,
  NavLink,
  Container,
} from 'reactstrap';
import LoginNav from './LoginNav';

export default class NavigationBar extends React.Component {
  constructor(props) {
    super(props);

    this.toggle = this.toggle.bind(this);

    this.state = {
      isOpen: false
    };
  }

  toggle() {
    this.setState({
      isOpen: !this.state.isOpen
    });
  }

  render() {
    return (
      <Navbar color='dark' dark sticky='top' expand='md'>
        <Container>
          <NavbarBrand href='/'>Something</NavbarBrand>
          <NavbarToggler onClick={this.toggle} />
          <Collapse isOpen={this.state.isOpen} navbar>
            <Nav className='mr-auto' navbar>
              <NavItem>
                <NavLink href='https://github.com/MaciekDudynski/cpp-rest-service'>GitHub</NavLink>
              </NavItem>
            </Nav>
            <LoginNav
              isLogedIn={this.props.isLogedIn}
              userLogin={this.props.userLogin}
              handleRegister={this.props.handleRegister}
              handleLogin={this.props.handleLogin}
              handleLogout={this.props.handleLogout} />
          </Collapse>
        </Container>
      </Navbar >
    );
  }
}

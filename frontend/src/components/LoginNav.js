import React from 'react';
import {
	Nav, NavItem, NavLink,
	Form, Button
} from 'reactstrap';
import LoginDropdown from './LoginDropdown';
import RegisterDropdown from './RegisterDropdown';

export default class LoginNav extends React.Component {
	constructor(props) {
		super(props);

		this.handleSubmit = this.handleSubmit.bind(this);
	}

	handleSubmit(event) {
		event.preventDefault();
		this.props.handleLogout();
	}

	render() {
		if (this.props.isLogedIn)
			return (
				<Nav className='ml-auto' navbar>
					<NavItem>
						<NavLink disabled href='#'>Welcome, {this.props.userLogin}</NavLink>
					</NavItem>
					<NavItem>
						<Form onSubmit={this.handleSubmit}>
							<Button block outline color='danger'>Logout</Button>
						</Form>
					</NavItem>
				</Nav>
			);
		else
			return (
				<Nav className='ml-auto' navbar>
					<RegisterDropdown handleRegister={this.props.handleRegister} />
					<LoginDropdown handleLogin={this.props.handleLogin} />
				</Nav>
			);
	}
}
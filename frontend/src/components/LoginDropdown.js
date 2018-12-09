import React from 'react';
import {
	Col,
	UncontrolledDropdown, DropdownToggle, DropdownMenu,
	FormGroup, Form, Button, Input
} from 'reactstrap';

export default class LoginDropdown extends React.Component {
	constructor(props) {
		super(props);

		this.handleInputChange = this.handleInputChange.bind(this);
		this.handleSubmit = this.handleSubmit.bind(this);
		this.setDefaultViewTimeout = null;

		this.state = {
			login: '',
			password: '',
			text: 'Login',
			color: 'info',
			enabled: true
		};
	}

	componentWillUnmount() {
		clearTimeout(this.setDefaultViewTimeout);
	}

	handleInputChange(event) {
		this.setState({
			[event.target.name]: event.target.value
		});
	}

	handleSubmit(event) {
		event.preventDefault();
		this.props.handleLogin(this.state.login, this.state.password)
			.then(returnCode => {
				if (returnCode === 200) {
					this.setState({ text: 'Logged successfully', color: 'success', enabled: false })
				} else if (returnCode === 401) {
					this.setState({ text: 'Invalid login or password', color: 'danger', enabled: false })
				} else {
					this.setState({ text: 'Unknown error', color: 'danger', enabled: false })
				}
				this.setDefaultViewTimeout = setTimeout(function () { this.setState({ text: 'Login', color: 'info', enabled: true }); }
					.bind(this), 3000);
			});
	}

	render() {
		return (
			<UncontrolledDropdown nav inNavbar>
				<DropdownToggle nav>
					<Button outline color='info'>Login</Button>
				</DropdownToggle>
				<DropdownMenu right className='login-dropdown'>
					<Form onSubmit={this.handleSubmit}>
						<Col sm={12}>
							<FormGroup row>
								<Col sm={12}>
									<Input name='login' placeholder='Login' onChange={this.handleInputChange} />
								</Col>
							</FormGroup>
							<FormGroup row>
								<Col sm={12}>
									<Input type='password' name='password' placeholder='Password' onChange={this.handleInputChange} />
								</Col>
							</FormGroup>
							<Button block outline color={this.state.color} disabled={!this.state.enabled}>{this.state.text}</Button>
						</Col>
					</Form>
				</DropdownMenu>
			</UncontrolledDropdown>
		);
	}
}
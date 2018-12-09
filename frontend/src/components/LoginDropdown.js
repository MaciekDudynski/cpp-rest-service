import React from 'react';
import {
	UncontrolledDropdown,
	DropdownToggle,
	DropdownMenu,
	Col,
	Button,
	Form, FormGroup,
	Input
} from 'reactstrap';

export default class LoginDropdown extends React.Component {
	constructor(props) {
		super(props);

		this.handleInputChange = this.handleInputChange.bind(this);
		this.handleSubmit = this.handleSubmit.bind(this);

		this.state = {
			login: '',
			password: ''
		};
	}

	handleInputChange(event) {
		this.setState({
			[event.target.name]: event.target.value
		});
	}

	handleSubmit(event) {
		event.preventDefault();
		this.props.handleLogin(this.state.login, this.state.password);
	}

	render() {
		return (
			<UncontrolledDropdown nav inNavbar>
				<DropdownToggle nav>
					<Button outline color='success'>Login</Button>
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
							<Button block outline color='success'>Login</Button>
						</Col>
					</Form>
				</DropdownMenu>
			</UncontrolledDropdown>
		);
	}
}
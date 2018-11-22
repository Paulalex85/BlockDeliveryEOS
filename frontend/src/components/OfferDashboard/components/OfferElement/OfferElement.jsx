import React, { Component } from 'react';
import { connect } from 'react-redux';

import Card from '@material-ui/core/Card';
import CardContent from '@material-ui/core/CardContent';
import Typography from '@material-ui/core/Typography';

class OfferElement extends Component {

    render() {
        const { offer } = this.props;

        return (
            <Card >
                <CardContent>
                    <Typography>Offer key : {offer.offerKey}</Typography>
                    <Typography>Order key : {offer.orderKey}</Typography>
                    <Typography>Place key : {offer.placeKey}</Typography>
                    <Typography>State : {offer.stateOffer}</Typography>
                </CardContent>
            </Card>
        )
    }
}

// Map all state to component props (for redux to connect)
const mapStateToProps = state => state;

// Export a redux connected component
export default connect(mapStateToProps)(OfferElement);
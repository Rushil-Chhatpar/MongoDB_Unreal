// import express
var express = require('express');
const { cp } = require('fs');
var app = express();
//import http
var http = require('http').Server(app);
var io = require('socket.io')(http);
// IF YOU WANT TO DO IT IN ONE LINE FOR WHATEVER REASON: var io = require('socket.io')(require('http').Server(require('express')()));
const mongoose = require('mongoose');

// access PORT environment variable
var port = process.env.PORT || 3000;
// tells the app to use the html found in the 'public' folder
app.use(express.static('public'));
//connect to MongoDB from mongoose
// URI = Uniform Resource Identifier
// use MongoDB URI to connect 
// its called 'connection string', get it from open MongoDB database
// if it connects 'then' create an arrow function (just like a lamda) to display a log
// if it doesn't connect then 'err' error to display a log
mongoose.connect('mongodb://localhost:27017/DBWorkshop', {})
        .then(() => console.log('You are connected to MongoDB!'))
        .catch(err => console.error('Something went wrong!', err));

{} // to end the line


// create Schemas for MongoDB
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const checkpointSchema = new mongoose.Schema(
    {
        name: String,
        isLastCheckpoint: Boolean
    }
);

const gameProgressSchema = new mongoose.Schema(
    {
        playerName: String,
        checkpoints: [checkpointSchema]
    }
);

const playerAbilitySchema = new mongoose.Schema(
    {
        name: String,
        iconPath: String,
        isEquipped: Boolean
    }
);

const playerSchema = new mongoose.Schema(
    {
        player: String,
        abilities: [playerAbilitySchema]
    }
)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Game consists of gameProgressSchema
const Game = mongoose.model('GameProgress', gameProgressSchema);
const Ability = mongoose.model('Ability', playerSchema);

function addAbility(player, abilityName, iconPath)
{
    return Ability.findOne({player, player}).then(progress =>
        {
            if(progress)
            {
                const abilityExists = progress.abilities.some(cp => cp.name === abilityName);
                if(!abilityExists)
                {
                    progress.abilities.forEach(cp => cp.isEquipped = false);
                    progress.abilities.push({ name: abilityName, iconPath: iconPath, isEquipped: true});
                }
                else
                {
                    progress.abilities.forEach(cp => cp.isEquipped = (cp.name === abilityName));
                }
                return progress.save();
            }
            else
            {
                const newProgress = new Ability(
                    {
                        player: player,
                        abilities: [{name: abilityName, iconPath: iconPath, isEquipped: true}]
                    }
                );
                return newProgress.save();
            }
        });
}

function addCheckpoint(playerName, checkpointName)
{
    // if found playerName
    return Game.findOne({playerName:playerName}).then(progress =>
        {
            // found the player
            if(progress)
            {
                // if the checkpointName == any of the checkpoints' name for that player
                const checkpointExists = progress.checkpoints.some(cp => cp.name === checkpointName);
                if(!checkpointExists)
                {
                    // Set all checkpoints to 'not last'
                    progress.checkpoints.forEach(cp => cp.isLastCheckpoint = false);
                    // add the new checkpoint as the last checkpoint
                    progress.checkpoints.push({ name: checkpointName, isLastCheckpoint: true});
                }
                else
                {
                    // Update the isLastCheckpoint flag for the existing checkpoint
                    progress.checkpoints.forEach(cp => cp.isLastCheckpoint = (cp.name === checkpointName));
                }
                // Save the data to DB
                return progress.save();
            }
            else
            {
                // Create a new schema entry
                const newProgress = new Game(
                    {
                        playerName: playerName,
                        checkpoints: [{name: checkpointName, isLastCheckpoint: true}]
                    }
                );
                // Save the data to DB
                return newProgress.save();
            }
        });
}

function getLastCheckpoint(playerName)
{
    return Game.findOne({playerName:playerName}).then(progress =>
        {
            if(progress && progress.checkpoints.length > 0)
            {
                const lastCheckpoint = progress.checkpoints.find(cp => cp.isLastCheckpoint === true);
                //return lastCheckpoint ? lastCheckpoint : null;
                return lastCheckpoint;
            }
            else
            {
                return null;
            }
        });
}

http.listen(port, function(){
    console.log('Listening on port ' + port);
});

io.on('connection', function(socket)
    {
        // on 'connection' perform function(socket)
        console.log('A user connected!');
        // on 'chat' event perform function(data)
        socket.on('chat', function(data)
        {
            console.log('CHAT: name: ' + data.name + ', message: ' + data.message);
            // broadcast 'chat' event
            io.sockets.emit('chat', data);
        });

        socket.on('save', function(data)
        {
            console.log('Checkpoint: Player: ' + data.player + ', checkpoint: ' + data.checkpoint);
            addCheckpoint(data.player, data.checkpoint);
        });

        socket.on('getlastcp', async function(data)
        {
            console.log('Checkpoint: player: ' + data.player);
            try
            {
                const lastCheckpoint = await getLastCheckpoint(data.player);
                if(lastCheckpoint)
                {
                    console.log('Last checkpoint for ', data.player, ':', lastCheckpoint);
                    socket.emit('getlastcp', lastCheckpoint);
                }
                else
                {
                    console.log('No checkpoint found for ', data.player);
                }
            }catch(error)
            {
                console.error('Error fetching the last checkpoint for ', data.player, ':', error);
            }
        });

        socket.on('addability', async function(data)
        {
            console.log('Ability: player: ' + data.playerName);
            addAbility(data.playerName, data.abilityName, data.iconPath);
        });
        
    }
);
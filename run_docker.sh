#!/bin/bash

# Name of the Docker image
IMAGE_NAME="cnc_image"

# Name of the Docker container
CONTAINER_NAME="cnc_container"

# Path in the container where the current directory will be mounted
CONTAINER_PROJECT_PATH="/project"

# Build the Docker image
docker build -t $IMAGE_NAME .

# Check if a container with the same name already exists
if [ $(docker ps -a -q -f name=$CONTAINER_NAME) ]; then
    # Stop and remove the existing container
    docker stop $CONTAINER_NAME
    docker rm $CONTAINER_NAME
fi

# Run the Docker container
docker run -it --name $CONTAINER_NAME -v "$(pwd)":$CONTAINER_PROJECT_PATH $IMAGE_NAME bash

# Note: "$(pwd)" will mount the current directory to the specified path inside the container

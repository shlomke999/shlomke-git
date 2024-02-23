#!/bin/bash


AWS_REGION="us-east-1"
stop_ec2_instances() {

  INSTANCE_IDS=$(aws ec2 describe-instances --region $AWS_REGION --filters "Name=instance-state-name,Values=running" --query "Reservations[].Instances[].InstanceId" --output text)


  for INSTANCE_ID in $INSTANCE_IDS; do
    echo "Stopping instance: $INSTANCE_ID"
    aws ec2 stop-instances --region $AWS_REGION --instance-ids $INSTANCE_ID
  done

  echo "EC2 instances successfully shut down."
}

stop_ec2_instances

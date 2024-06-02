resource "aws_instance" "cerberus" {
  ami = var.ami
  instance_type = var.instance_type
}

# This is if you intended to log with ssh
# It requires a ssh private-public key pair in this directory
# More info here:
# https://registry.terraform.io/providers/hashicorp/aws/latest/docs/resources/key_pair
resource "aws_key_pair" "your-ssh-key" {
    key_name = "your_ssh"
    public_key = file(".ssh/your_ssh.pub")
}

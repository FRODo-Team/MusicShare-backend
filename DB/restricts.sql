ALTER TABLE Users
ADD CONSTRAINT FK_ULF FOREIGN KEY (UserID) REFERENCES Likes(LikeFrom),
ADD CONSTRAINT FK_ULT FOREIGN KEY (UserID) REFERENCES Likes(LikeTo),
ADD CONSTRAINT FK_UC FOREIGN KEY (UserID) REFERENCES Channel(AdminID);

ALTER TABLE Song
ADD CONSTRAINT SGenre_CHK CHECK (Year <= 2021),
ADD CONSTRAINT SGenre_CHK CHECK (Genre = 'Rock' OR Genre = 'Jazz' OR
				Genre = 'Dubstep' OR Genre = 'Techno' OR
				Genre = 'Pop' OR Genre = 'Electro' OR
				Genre = 'Country' OR Genre = 'Indie')

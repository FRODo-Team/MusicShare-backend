ALTER TABLE Song
ADD CONSTRAINT SGenre_CHK CHECK (Year <= 2021),
ADD CONSTRAINT SGenre_CHK CHECK (Genre = 'Rock' OR Genre = 'Jazz' OR
				Genre = 'Dubstep' OR Genre = 'Techno' OR
				Genre = 'Pop' OR Genre = 'Electro' OR
				Genre = 'Country' OR Genre = 'Indie')
